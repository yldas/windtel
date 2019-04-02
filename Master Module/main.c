/*WindTel Libraries*/
#include "DriverLibFiles/driverlib.h"
#include "WindTel_Graphic.h"
#include "WindTel_I2C.h"

/* Standard Define Libraries */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Time period for timer A1, control module interrupt*/
#define TIMER_PERIOD    11718

/* Slave Address for I2C Slave */
#define SLAVE_ADDRESS_PRESSURE       0x000B
#define SLAVE_ADDRESS_DYNAMIC       0x000C
#define NUM_OF_REC_BYTES_DYNAMIC    11

/* Variables */
const uint8_t TXData[] = {0x19};
static char RXData[NUM_OF_REC_BYTES_DYNAMIC];
static volatile uint32_t xferIndex;

// Graphic library context
Graphics_Context g_sContext;
Graphics_Rectangle rect;
float currentSpeed = 0;
int cursor = 1;
int menuIndex = 1;
int on_off = 1;
int potentiometerStep = 0;
char rodLength[6];
int rod_Length = 0;
int seconds = 5;
int selectedPressureSensors[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int selectedWindForces[7] = {0,0,0,0,0,0,0};
int selectedTempHumd[2] ={0,0};
bool balanceSelected, pressureSelected, tempSelected, humidSelected = false;
/* I2C Master Configuration Parameter */
const eUSCI_I2C_MasterConfig i2cConfig =
{
 EUSCI_B_I2C_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
 3000000,                                // SMCLK = 3MHz
 EUSCI_B_I2C_SET_DATA_RATE_100KBPS,      // Desired I2C Clock of 100khz
 0,                                      // No byte counter threshold
 EUSCI_B_I2C_NO_AUTO_STOP                // No Autostop
};

const Timer_A_UpModeConfig upConfig =
{
 TIMER_A_CLOCKSOURCE_ACLK,              // ACLK Clock Source
 TIMER_A_CLOCKSOURCE_DIVIDER_1,          // ACLK/1 = 3MHz
 TIMER_PERIOD,                           // 5000 tick period
 TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
 TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
 TIMER_A_DO_CLEAR                        // Clear value
};

const Timer_A_UpModeConfig experimentTimeConfig =
{
 TIMER_A_CLOCKSOURCE_ACLK,              // ACLK Clock Source
 TIMER_A_CLOCKSOURCE_DIVIDER_1,          // ACLK/1 = 3MHz
 128000,                           // 5000 tick period
 TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
 TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
 TIMER_A_DO_CLEAR                        // Clear value
};

//Main program of the master module
void main(void){
    WDT_A_hold(WDT_A_BASE);

    /* Initialize Buttton Setup. */
    boardInit();
    clockInit();

    // LCD setup using Graphics Library API calls
    Kitronix320x240x16_SSD2119Init();
    Graphics_initContext(&g_sContext, &g_sKitronix320x240x16_SSD2119);

    // Control Module Pin Setup
    P2->DIR |= BIT0 + BIT1 + BIT2 + BIT3;
    P2->OUT |= BIT0 + BIT1 + BIT2 + BIT3;

    //Turn off LCD
    P2->OUT &= ~(BIT7);

    /* Configuring Timer_A1 for Up Mode produce 250ms pulses to increment and decrement speed*/
    MAP_Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig);
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &experimentTimeConfig);

    // I2C Pin Setup
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
                                                   GPIO_PIN6 + GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    I2C_Init(EUSCI_B2_BASE,&i2cConfig,SLAVE_ADDRESS_DYNAMIC,INT_EUSCIB2,RXData, NUM_OF_REC_BYTES_DYNAMIC);

    /* Enabling interrupts and starting the timer */
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_Interrupt_enableInterrupt(INT_TA0_0);
    MAP_Interrupt_enableInterrupt(INT_TA1_0);

    //PushButton Setup
    P5->DIR &= ~(BIT1 + BIT2 + BIT5 + BIT6 + BIT7);
    P5->IE = BIT1 + BIT2 + BIT5 + BIT6 + BIT7;
    P5->IFG = 0;

    drawMainMenu(g_sContext,rect);
    __no_operation();
    __enable_irq();
    NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);

    while(on_off){
        __sleep();
        __no_operation();
        __enable_irq();
        NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);
    }
}

void PORT5_IRQHandler(void){
    //    ON/OFF Button
    if(P5->IFG & BIT1){
        if(on_off){
            P2->OUT |= BIT7;
            on_off = 0;
        }
        else{
            P2->OUT &= ~(BIT7);
            on_off = 1;
        }
    }
    //Right Button
    if(!on_off){
        if(P5->IFG & BIT5){
            if(menuIndex == 1){
                nextOption(g_sContext, rect, menuIndex,cursor,rod_Length);
                cursor++;
                if(cursor == 6)
                    cursor = 1;
            }
            else if(menuIndex == 3){
                nextOption(g_sContext,rect,menuIndex,cursor,rod_Length);
                cursor++;
                if(cursor == 4)
                    cursor = 1;
            }
            else if(menuIndex == 4){
                nextOption(g_sContext, rect,menuIndex,cursor,rod_Length);
                cursor++;
                if(cursor == 4)
                    cursor = 1;
            }
            else if(menuIndex == 6){
                nextOption(g_sContext, rect,menuIndex,cursor,rod_Length);
                cursor++;
                if(cursor == 7)
                    cursor = 1;
            }
            else if(menuIndex == 7 || menuIndex == 8){
                nextSensor(g_sContext, rect,menuIndex,cursor);
                cursor++;
                if(cursor == 12)
                    cursor = 1;
            }
            else if(menuIndex == 9){
                nextForce(g_sContext, rect,menuIndex,cursor);
                cursor++;
                if(cursor == 8)
                    cursor = 1;
            }
            else if(menuIndex == 10){
                nextOption(g_sContext, rect,menuIndex,cursor,rod_Length);
                cursor++;
                if(cursor == 5)
                    cursor = 1;
            }
            else if(menuIndex == 11){
                nextOption(g_sContext, rect,menuIndex,cursor,rod_Length);
                cursor++;
                if(cursor == 8)
                    cursor = 1;
            }
        }
    }
    //Left Button
    if(P5->IFG & BIT2 && !on_off){
        if(menuIndex == 1){
            previousOption(g_sContext, rect, menuIndex,cursor,rod_Length);
            cursor--;
            if(cursor == 0)
                cursor = 5;
        }
        else if(menuIndex == 3){
            previousOption(g_sContext,rect,menuIndex,cursor,rod_Length);
            cursor--;
            if(cursor == 0)
                cursor = 3;
        }
        else if(menuIndex == 4){
            previousOption(g_sContext, rect,menuIndex,cursor,rod_Length);
            cursor--;
            if(cursor == 0)
                cursor = 3;
        }
        else if(menuIndex == 6){
            previousOption(g_sContext, rect,menuIndex,cursor,rod_Length);
            cursor--;
            if(cursor == 0)
                cursor = 6;
        }
        else if(menuIndex == 7 || menuIndex == 8){
            previousSensor(g_sContext, rect,menuIndex,cursor);
            cursor--;
            if(cursor == 0)
                cursor = 11;
        }
        else if(menuIndex == 9){
            previousForce(g_sContext, rect,menuIndex,cursor);
            cursor--;
            if(cursor == 0)
                cursor = 7;
        }
        else if(menuIndex == 10){
            previousOption(g_sContext, rect,menuIndex,cursor,rod_Length);
            cursor--;
            if(cursor == 0)
                cursor = 4;
        }
        else if(menuIndex == 11){
            previousOption(g_sContext, rect,menuIndex,cursor,rod_Length);
            cursor--;
            if(cursor == 0)
                cursor = 7;
        }
    }

    //Confirm Button
    if(P5->IFG & BIT6 && !on_off){
        if(menuIndex == 1){
            if(cursor == 1){
                SYSCTL->REBOOT_CTL = 0x6901;
            }
            if(cursor == 3){
                drawPerformExperimentMenu(g_sContext, rect);
                cursor = 1;
                menuIndex = 3;
            }
            if(cursor == 4){
                drawSpeedControlMenu(g_sContext, rect);
                cursor = 1;
                menuIndex = 4;
                xferIndex = 0;
                I2C_Init(EUSCI_B2_BASE,&i2cConfig,SLAVE_ADDRESS_DYNAMIC,INT_EUSCIB2,RXData, NUM_OF_REC_BYTES_DYNAMIC);
                I2C_StartCommunication(EUSCI_B2_BASE,TXData);
            }
        }
        else if(menuIndex == 3){
            if(cursor == 1){
                if(rod_Length<500)
                    rod_Length++;
                updateRodLength(g_sContext,rod_Length,rect);
            }
            if(cursor == 2){
                drawParameterMenu(g_sContext,rect);
                menuIndex = 6;
                cursor = 1;
                int i = 0;
                for(i; i<2; i++)
                    if(selectedTempHumd[i])
                        selectTempHumid(g_sContext, rect, i+3);
            }
            if(cursor == 3){
                drawMainMenu(g_sContext,rect);
                menuIndex = 1;
                cursor = 1;
            }
        }

        else if(menuIndex == 4){
            if(cursor == 1){
                potentiometerStep = 0;
                MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
                /* Enabling MASTER interrupts */
                MAP_Interrupt_enableMaster();
                P2->OUT &= ~BIT2;
            }
            else if(cursor == 2){
                potentiometerStep = 1;
                MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
                /* Enabling MASTER interrupts */
                MAP_Interrupt_enableMaster();
                P2->OUT &= ~BIT3;
            }
            else if(cursor == 3){
                MAP_Timer_A_stopTimer(TIMER_A0_BASE);
                P2->OUT |= BIT1;
                Delay(1000);
                P2->OUT |= BIT0;
                Delay(1000);
                drawMainMenu(g_sContext,rect);
                menuIndex = 1;
                cursor = 1;
            }
        }
        else if(menuIndex == 6){
            if(cursor == 1){
                drawPressureMenu(g_sContext,rect);
                menuIndex = 7;
                cursor = 1;
                int i = 1;
                for(i; i<= 9; i++)
                    if(selectedPressureSensors[i])
                        selectSensor(g_sContext, rect, i);

            }
            if(cursor == 2){
                drawForceMenu(g_sContext,rect);
                menuIndex = 9;
                cursor = 1;
                int i = 0;
                for(i; i< 7; i++)
                    if(selectedWindForces[i])
                        selectForce(g_sContext, rect, i);
            }
            if(cursor == 3){
                if(selectedTempHumd[0]){
                    deselectTempHumid(g_sContext, rect, cursor);
                    selectedTempHumd[0] = 0;
                    tempSelected = false;
                }

                else{
                    selectTempHumid(g_sContext, rect, cursor);
                    selectedTempHumd[0] = 1;
                    tempSelected = true;
                }
            }
            if(cursor == 4){
                if(selectedTempHumd[1]){
                    deselectTempHumid(g_sContext, rect, cursor);
                    selectedTempHumd[1] = 0;
                    humidSelected = false;
                }

                else{
                    selectTempHumid(g_sContext, rect, cursor);
                    selectedTempHumd[1] = 1;
                    humidSelected = true;
                }
            }
            if(cursor == 5){
                drawExperimentDurationMenu(g_sContext,rect);
                menuIndex = 10;
                cursor = 1;
            }
            if(cursor == 6){
                drawMainMenu(g_sContext,rect);
                menuIndex = 1;
                cursor = 1;
            }
        }
        else if(menuIndex == 7){
            if(cursor == 1){
                if(selectedPressureSensors[cursor+10] == 1 || selectedPressureSensors[cursor] == 1){
                    deselectSensor(g_sContext, rect, cursor);
                    selectedPressureSensors[cursor] = 0;
                    selectedPressureSensors[cursor+10] = 0;
                    pressureSelected = false;
                }

                else{
                    selectSensor(g_sContext, rect, cursor);
                    selectedPressureSensors[cursor] = 1;
                    selectedPressureSensors[cursor+10] = 1;
                    pressureSelected = true;
                }
            }
            else if(cursor > 1 && cursor < 10){
                if(selectedPressureSensors[cursor] == 1){
                    deselectSensor(g_sContext, rect, cursor);
                    selectedPressureSensors[cursor] = 0;
                    pressureSelected = false;
                }

                else{
                    selectSensor(g_sContext, rect, cursor);
                    selectedPressureSensors[cursor] = 1;
                    pressureSelected = true;
                }

            }

            if(cursor == 10){
                drawMorePressureMenu(g_sContext,rect);
                menuIndex = 8;
                cursor = 1;
                int i = 10;
                for(i; i<= 19; i++)
                    if(selectedPressureSensors[i])
                        selectSensor(g_sContext, rect, i-10);

            }
            if(cursor == 11){
                drawParameterMenu(g_sContext,rect);
                menuIndex = 6;
                cursor = 1;
                int i = 0;
                for(i; i<2; i++)
                    if(selectedTempHumd[i])
                        selectTempHumid(g_sContext, rect, i+3);
            }
        }
        else if(menuIndex == 8){
            if(cursor == 1){
                if(selectedPressureSensors[cursor+10] == 1 || selectedPressureSensors[cursor] == 1){
                    deselectSensor(g_sContext, rect, cursor);
                    selectedPressureSensors[cursor] = 0;
                    selectedPressureSensors[cursor+10] = 0;
                    pressureSelected = false;
                }

                else{
                    selectSensor(g_sContext, rect, cursor);
                    selectedPressureSensors[cursor] = 1;
                    selectedPressureSensors[cursor+10] = 1;
                    pressureSelected = true;
                }
            }
            else if(cursor > 1 && cursor < 10){
                if(selectedPressureSensors[cursor+10] == 1){
                    deselectSensor(g_sContext, rect, cursor);
                    selectedPressureSensors[cursor+10] = 0;
                    pressureSelected = false;
                }

                else{
                    selectSensor(g_sContext, rect, cursor);
                    selectedPressureSensors[cursor+10] = 1;
                    pressureSelected = true;
                }

            }
            else if(cursor == 10){

            }
            else if(cursor == 11){
                drawParameterMenu(g_sContext,rect);
                menuIndex = 6;
                int i = 0;
                cursor = 1;
                for(i; i<2; i++)
                    if(selectedTempHumd[i])
                        selectTempHumid(g_sContext, rect, i+3);
            }
        }
        else if(menuIndex == 9){
            if(cursor > 0 && cursor < 7){
                if(selectedWindForces[cursor]){
                    deselectForce(g_sContext, rect, cursor);
                    selectedWindForces[cursor] = 0;
                    balanceSelected = false;
                }
                else{
                    selectForce(g_sContext, rect, cursor);
                    selectedWindForces[cursor] = 1;
                    balanceSelected = true;
                }
            }

            else if(cursor == 7){
                drawParameterMenu(g_sContext,rect);
                menuIndex = 6;
                cursor = 1;
                int i = 0;
                for(i; i<2; i++)
                    if(selectedTempHumd[i])
                        selectTempHumid(g_sContext, rect, i+3);
            }
        }
        else if(menuIndex == 10){
            if(cursor == 1 && seconds<300){
                seconds++;
                updateTimeDuration(g_sContext,seconds,rect);
            }
            else if(cursor == 2){
                drawSampleMenu(g_sContext,rect);
                menuIndex = 11;
                cursor = 1;
                //                MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
                //                /* Enabling MASTER interrupts */
                //                MAP_Interrupt_enableMaster();
            }
            else if(cursor == 3){
                drawParameterMenu(g_sContext,rect);
                menuIndex = 6;
                cursor = 1;
                int i = 0;
                for(i; i<2; i++)
                    if(selectedTempHumd[i])
                        selectTempHumid(g_sContext, rect, i+3);
            }
            else if(cursor == 4){
                drawMainMenu(g_sContext,rect);
                menuIndex = 1;
                cursor = 1;
            }
        }
        else if(menuIndex == 11){
            if(cursor == 1){

            }
            else if(cursor == 2){

            }
            else if(cursor == 3){

            }
            else if(cursor == 4){

            }
            else if(cursor == 5){

            }
            else if(cursor == 6){
                drawExperimentDurationMenu(g_sContext,rect);
                menuIndex = 10;
                cursor = 1;
            }
            else if(cursor == 7){
                drawMainMenu(g_sContext,rect);
                menuIndex = 1;
                cursor = 1;
            }
        }
    }
    if(P5->IFG & BIT7 && !on_off){
        if(menuIndex == 3){
            if(cursor == 1){
                if(rod_Length>0)
                    rod_Length--;
                updateRodLength(g_sContext,rod_Length,rect);
            }
        }
        if(menuIndex == 10){
            if(seconds>5){
                seconds--;
                updateTimeDuration(g_sContext,seconds,rect);
            }
        }
    }

    P5->IFG = 0;
}

void TA0_0_IRQHandler(void)
{
    //    updateWindSpeed(g_sContext,RXData);
}

void TA1_0_IRQHandler(void)
{
    if(potentiometerStep)
        P2->OUT |= BIT3;
    else
        P2->OUT |= BIT2;

    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
                                             TIMER_A_CAPTURECOMPARE_REGISTER_0);
    MAP_Timer_A_stopTimer(TIMER_A1_BASE);
}

void EUSCIB2_IRQHandler(void)
{
    uint_fast16_t status;

    status = MAP_I2C_getEnabledInterruptStatus(EUSCI_B2_BASE);
    MAP_I2C_clearInterruptFlag(EUSCI_B2_BASE, status);

    /* Receives bytes into the receive buffer. If we have received all bytes,
     * send a STOP condition */
    if (status & EUSCI_B_I2C_RECEIVE_INTERRUPT0)
    {
        if (xferIndex == NUM_OF_REC_BYTES_DYNAMIC - 2)
        {
            MAP_I2C_disableInterrupt(EUSCI_B2_BASE,
                                     EUSCI_B_I2C_RECEIVE_INTERRUPT0);
            MAP_I2C_enableInterrupt(EUSCI_B2_BASE, EUSCI_B_I2C_STOP_INTERRUPT);

            /*
             * Switch order so that stop is being set during reception of last
             * byte read byte so that next byte can be read.
             */
            MAP_I2C_masterReceiveMultiByteStop(EUSCI_B2_BASE);
            RXData[xferIndex++] = MAP_I2C_masterReceiveMultiByteNext(
                    EUSCI_B2_BASE);
        } else
        {
            RXData[xferIndex++] = MAP_I2C_masterReceiveMultiByteNext(
                    EUSCI_B2_BASE);
        }
    }
    else if (status & EUSCI_B_I2C_STOP_INTERRUPT)
    {
        MAP_Interrupt_disableSleepOnIsrExit();
        MAP_I2C_disableInterrupt(EUSCI_B2_BASE,
                                 EUSCI_B_I2C_STOP_INTERRUPT);
    }
    if(menuIndex == 4 && xferIndex == 10){
        updateWindSpeed(g_sContext,RXData);
    }
}
