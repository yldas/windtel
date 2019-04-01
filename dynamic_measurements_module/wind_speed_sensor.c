/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdlib.h>
#include <stdint.h>

int delay = 0;

/* Constant definitions */
#define TIMER_PERIOD                         65535
#define CAPTURE_VALUES_BUFFER_CAPACITY       5

/* I2C Results */
double windSpeedInMetersPerSecond;
double windSpeedInMilesPerHour;

/* Timer_A Up/Down Mode Configuration Parameter */
const Timer_A_UpDownModeConfig upDownModeConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,            // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_32,      // SMCLK/1 = 3MHz
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

/* Statics */
static volatile uint_fast16_t captureValues[CAPTURE_VALUES_BUFFER_CAPACITY];
static volatile uint32_t captureValuesPointer = 0;
static volatile double captureValuesTimeDifference[CAPTURE_VALUES_BUFFER_CAPACITY - 1];
static volatile uint_fast16_t threshold = 0;
static volatile uint_fast16_t queueSize = 0;
static volatile double averageFrequency = 0;

/* Functions declarations */
double convertToMetersPerSecond(double frequency);
double convertToMilesPerHour(double frequency);

int main(void)
{
    /* Stop watchdog timer */
    MAP_WDT_A_holdTimer();

    /* Configuring P1.0 as output */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    /* Configuring P2.4 as peripheral input for capture */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting ACLK = VLO = 14kHz and dividing by 16 = 875Hz */
    //MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Configuring Capture Mode */
    MAP_Timer_A_initCapture(TIMER_A0_BASE, &captureModeConfig);

    /* Configuring Up/Down Mode */
    MAP_Timer_A_configureUpDownMode(TIMER_A0_BASE, &upDownModeConfig);

    /* Enabling interrupts and going to sleep */
    //MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableInterrupt(INT_TA0_N);
    MAP_Timer_A_enableInterrupt(TIMER_A0_BASE);
    MAP_Interrupt_enableMaster();

    /* Starting the TIMER_A0 in up/down mode */
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UPDOWN_MODE);

    /*
    while (1) {
        // do nothing
    }
    */

    MAP_PCM_gotoLPM0();
}

//******************************************************************************
//
//This is the TIMERA interrupt vector service routine.
//
//******************************************************************************
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
        if (delay%500 == 0) {
            delay = 0;
        }
        delay++;
        // Compute result
        windSpeedInMetersPerSecond = convertToMetersPerSecond(averageFrequency);
        windSpeedInMilesPerHour = convertToMilesPerHour(averageFrequency);
        }
    }
}

/* Function definitions */
double convertToMetersPerSecond(double frequency) {
    return frequency * 0.098;
}
double convertToMilesPerHour(double frequency) {
    return 2.23694 * convertToMetersPerSecond(frequency);
}
