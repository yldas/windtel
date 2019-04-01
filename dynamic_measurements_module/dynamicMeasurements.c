/* DriverLib includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard C library includes */
#include <stdint.h>
#include <math.h>

int delay = 0;

/* DHT11 Globals */
int ack = 0;
int lowToHighTimeStamps[41];
int bit = 0;
int pulseWidths[40];
int bits[40];
int humInt = 0;
int humDec = 0;
int tempInt = 0;
int tempDec = 0;
int checkSum = 0;
int DHT11Done = 0;

/* I2C Results */
int relativeHumidity;
int temperature;
double windSpeedInMetersPerSecond;
//double windSpeedInMilesPerHour;

/* Constant definitions for DHT11 Sensor */
#define POWERUP_TIMER_PERIOD            46875
#define START_SIGNAL_TIMER_PERIOD       1000
#define DATA_PULSE_WIDTH_TIMER_PERIOD   3000000
#define SAMPLE_RATE_TIMER_PERIOD        46875

/* Constant definitions for Wind Speed Sensor */
#define TIMER_PERIOD                    65535
#define CAPTURE_VALUES_BUFFER_CAPACITY  5

/* DHT11 Parameters */
const Timer_A_UpModeConfig powerUpTimerConfig =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_64,
     POWERUP_TIMER_PERIOD,
     TIMER_A_TAIE_INTERRUPT_DISABLE,
     TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
     TIMER_A_DO_CLEAR
};

const Timer_A_UpModeConfig startSignalTimerConfig =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_64,
     START_SIGNAL_TIMER_PERIOD,
     TIMER_A_TAIE_INTERRUPT_DISABLE,
     TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
     TIMER_A_DO_CLEAR
};

const Timer_A_UpModeConfig dataPulseWidthTimerConfig =
{
     TIMER_A_CLOCKSOURCE_SMCLK,
     TIMER_A_CLOCKSOURCE_DIVIDER_1,
     DATA_PULSE_WIDTH_TIMER_PERIOD,
     TIMER_A_TAIE_INTERRUPT_DISABLE,
     TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
     TIMER_A_DO_CLEAR
};

/* Wind Speed sensor Timer_A parameters */
const Timer_A_UpDownModeConfig upDownModeConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,           // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_32,      // SMCLK/1 = 93.750kHz
        TIMER_PERIOD,
        TIMER_A_TAIE_INTERRUPT_DISABLE,      // Disable Timer ISR
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
        TIMER_A_SKIP_CLEAR                   // Skip Clear Counter
};

/* Timer_A Capture Mode Configuration Parameter */
const Timer_A_CaptureModeConfig captureModeConfig =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,        // CC Register 1
        TIMER_A_CAPTUREMODE_RISING_EDGE,          // Rising Edge
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA Input Select
        TIMER_A_CAPTURE_SYNCHRONOUS,              // Synchronized Capture
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  // Enable interrupt
        TIMER_A_OUTPUTMODE_OUTBITVALUE            // Output bit value
};

/* Wind Speed Sensor Statics */
static volatile uint_fast16_t captureValues[CAPTURE_VALUES_BUFFER_CAPACITY];
static volatile uint32_t captureValuesPointer = 0;
static volatile double captureValuesTimeDifference[CAPTURE_VALUES_BUFFER_CAPACITY - 1];
static volatile uint_fast16_t threshold = 0;
static volatile uint_fast16_t queueSize = 0;
static volatile double averageFrequency = 0;

/* Wind Speed Sensor Function declarations */
double convertToMetersPerSecond(double frequency);
double convertToMilesPerHour(double frequency);

/* DHT11 Function declarations */
void convertToBits();
void convertToValues();

int main(void)
{
    /* Stop WDT */
    MAP_WDT_A_holdTimer();

    ////////////////////////////// DHT11 PHASE ////////////////////////////////////
    /* Configure timers in Up Mode */
    MAP_Timer_A_configureUpMode(TIMER_A3_BASE, &powerUpTimerConfig);            // wait 1 second after power-up
    MAP_Timer_A_configureUpMode(TIMER_A1_BASE, &startSignalTimerConfig);        // hold start signal for 500us
    MAP_Timer_A_configureUpMode(TIMER_A2_BASE, &dataPulseWidthTimerConfig);     // measure pulse-width of data bit

    /* LCD Debugging */
    P3->DIR |= BIT7; // RS
    P3->DIR |= BIT6; // RW
    P3->DIR |= BIT5; // E
    setPort(4, 0x00);
    LCD_init(4, 3, 6, 3, 7, 3, 5);

    /* Clear timers */
    MAP_Timer_A_clearTimer(TIMER_A2_BASE);

    /* Enable interrupts */
    MAP_Interrupt_enableInterrupt(INT_TA3_0);
    MAP_Interrupt_enableInterrupt(INT_TA1_0);
    MAP_Interrupt_enableInterrupt(INT_TA3_0);
    MAP_Interrupt_enableInterrupt(INT_PORT2);

    /* Configure GPIO */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN5);

    /* Start power-up timer */
    MAP_Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_UP_MODE);

    /* Enable Master interrupts */
    MAP_Interrupt_enableMaster();

    /* Main loop */
    while (bit <= 40) {
        // do nothing
    }

    /* Stop and clear timer */
    MAP_Timer_A_stopTimer(TIMER_A2_BASE);
    MAP_Timer_A_clearTimer(TIMER_A2_BASE);

    int n;
    for (n = 0; n <= 40; n++) {
        pulseWidths[n] = ((lowToHighTimeStamps[n + 1] - lowToHighTimeStamps[n]) / 3.0) - 50;
    }

    /* Get results */
    convertToBits();
    convertToValues();

    /* Get Results */
    relativeHumidity = humInt;
    temperature = tempInt;

    ////////////////////////////// WIND SPEED SENSOR PHASE ////////////////////////////////////
    /* Configuring P2.4 as peripheral input for capture */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring Capture Mode */
    MAP_Timer_A_initCapture(TIMER_A0_BASE, &captureModeConfig);

    /* Configuring Up/Down Mode */
    MAP_Timer_A_configureUpDownMode(TIMER_A0_BASE, &upDownModeConfig);

    /* Enabling interrupts and going to sleep */
    MAP_Interrupt_enableInterrupt(INT_TA0_N);
    MAP_Timer_A_enableInterrupt(TIMER_A0_BASE);

    /* Starting the TIMER_A3 in up/down mode */
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UPDOWN_MODE);

    while (1) {
        // do nothing
    }
}

/* Interrupt handler for power-up timer */
void TA3_0_IRQHandler(void)
{
    /* Stop timer */
    MAP_Timer_A_stopTimer(TIMER_A3_BASE);

    /* Clear timer */
    MAP_Timer_A_clearTimer(TIMER_A3_BASE);

    /* Clear flag */
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE,
                                             TIMER_A_CAPTURECOMPARE_REGISTER_0);

    /* Send start signal */
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN5);

    /* Start start signal timer */
    MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
}

/* Interrupt handler for start signal timer */
void TA1_0_IRQHandler(void)
{
    /* Stop timer */
    MAP_Timer_A_stopTimer(TIMER_A1_BASE);

    /* Clear timer */
    MAP_Timer_A_clearTimer(TIMER_A1_BASE);

    /* Clear flag */
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
                                             TIMER_A_CAPTURECOMPARE_REGISTER_0);

    /* Configure P2.4 as negative-edge interrupt-enabled input to detect DHT22 response signal */
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);   //  precautionary measure
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN5,
                                 GPIO_HIGH_TO_LOW_TRANSITION);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN5);
}

/* Interrupt handler for event capture */
void TA0_N_IRQHandler(void)
{
    if ((MAP_Timer_A_getCaptureCompareInterruptStatus(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG)) == TIMER_A_CAPTURECOMPARE_INTERRUPT_FLAG) {
    uint32_t jj;
    uint32_t kk;
    uint32_t ii;
    double temp;

    /* Clear flag */
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_1);

    /* Shift queue */
    jj = 9;
    while (jj > 0) {
        captureValues[jj] = captureValues[jj - 1];
        jj--;
    }

    /* Enqueue new capture value */
    captureValues[0] =
            MAP_Timer_A_getCaptureCompareCount(TIMER_A0_BASE,
                                             TIMER_A_CAPTURECOMPARE_REGISTER_1);

    /* Check if threshold for calculations has been reached */
    if (queueSize == CAPTURE_VALUES_BUFFER_CAPACITY - 1) {
        threshold++;
    } else {
        queueSize++;
    }

    /* If threshold is reached, proceed with calculations */
    if (threshold) {
    // Convert to time difference values
    for (kk = 0; kk < CAPTURE_VALUES_BUFFER_CAPACITY - 1; kk++) {
        captureValuesTimeDifference[kk] = abs((captureValues[kk] - captureValues[kk + 1])) / 93750.0;     // 3.0E6 is due to SMCLK = 3MHz
    }
    // Take average of time difference values
    temp = 0;
    for (ii = 0; ii < CAPTURE_VALUES_BUFFER_CAPACITY - 1; ii++) {
        temp += captureValuesTimeDifference[ii];
    }
    // Calculate average frequency
    averageFrequency = (CAPTURE_VALUES_BUFFER_CAPACITY - 1) / temp;
    int freq = averageFrequency;
    /*
    if (delay % 500 == 0) {
        LCD_busy2(4, 3, 6, 3, 7, 3, 5);
        clearLCD(4, 3, 6, 3, 7, 3, 5);
        LCD_busy2(4, 3, 6, 3, 7, 3, 5);
        writeCommand(4, 3, 6, 3, 7, 3, 5, 'n', "Frequency: ");
        LCD_busy2(4, 3, 6, 3, 7, 3, 5);
        showNumber(4, 3, 6, 3, 7, 3, 5, freq);
        LCD_busy2(4, 3, 6, 3, 7, 3, 5);
        writeCommand(4, 3, 6, 3, 7, 3, 5, 'n', "Hz");
        delay = 0;
    }
    */
    delay++;
    // Compute result
    windSpeedInMetersPerSecond = convertToMetersPerSecond(averageFrequency);
    //windSpeedInMilesPerHour = convertToMilesPerHour(averageFrequency);
        }
    }
}

/* Interrupt handler for P2.4 */
void PORT2_IRQHandler(void)
{
    if (MAP_GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN5) & GPIO_PIN5) {
        /* Clear flag */
        MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);
        if (ack == 0) {
            ack++;
        } else if (ack == 1) {
            ack++;
            /* Store time-stamp of data bit start */
            lowToHighTimeStamps[bit++] = MAP_Timer_A_getCounterValue(TIMER_A2_BASE);
            /* Start data pulse width timer */
            MAP_Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);
        } else {
            /* Store time-stamp of data bit start */
            lowToHighTimeStamps[bit++] = MAP_Timer_A_getCounterValue(TIMER_A2_BASE);
        }
    }
}

void convertToBits()
{
    int i;
    for (i = 0; i < 40; i++) {
        if (pulseWidths[i] > 70) {
            bits[i] = 1;
        } else {
            bits[i] = 0;
        }
    }
}

void convertToValues()
{
    int i;
    for (i = 7; i >= 0; i--) {
        if (bits[7 - i] == 1) {
            humInt += pow(2.0, i);
            LCD_busy2(4, 3, 6, 3, 7, 3, 5);
            clearLCD(4, 3, 6, 3, 7, 3, 5);
            LCD_busy2(4, 3, 6, 3, 7, 3, 5);
            writeCommand(4, 3, 6, 3, 7, 3, 5, 'n', "Humidity: ");
            LCD_busy2(4, 3, 6, 3, 7, 3, 5);
            showNumber(4, 3, 6, 3, 7, 3, 5, humInt);
            LCD_busy2(4, 3, 6, 3, 7, 3, 5);
            writeCommand(4, 3, 6, 3, 7, 3, 5, 'n', "%");
        }
    }
    for (i = 15; i >= 8; i--) {
        if (bits[23 - i] == 1) {
            humDec += pow(2.0, i - 8);
        }
    }
    for (i = 23; i >= 16; i--) {
        if (bits[39 - i] == 1) {
            tempInt += pow(2.0, i - 16);
            /*
            LCD_busy2(4, 3, 6, 3, 7, 3, 5);
            clearLCD(4, 3, 6, 3, 7, 3, 5);
            LCD_busy2(4, 3, 6, 3, 7, 3, 5);
            writeCommand(4, 3, 6, 3, 7, 3, 5, 'n', "Temperature: ");
            LCD_busy2(4, 3, 6, 3, 7, 3, 5);
            showNumber(4, 3, 6, 3, 7, 3, 5, tempIntBuff[transmissions]);
            LCD_busy2(4, 3, 6, 3, 7, 3, 5);
            writeCommand(4, 3, 6, 3, 7, 3, 5, 'n', "C");
            */
        }
    }
    for (i = 31; i >= 24; i--) {
        if (bits[55 - i] == 1) {
            tempDec += pow(2.0, i - 24);
        }
    }
    for (i = 39; i >= 32; i--) {
        if (bits[71 - i] == 1) {
            checkSum += pow(2.0, i - 32);
        }
    }
}

/* Wind Speed Sensor Function definitions */
double convertToMetersPerSecond(double frequency) {
    return frequency * 0.098;
}
double convertToMilesPerHour(double frequency) {
    return 2.23694 * convertToMetersPerSecond(frequency);
}
