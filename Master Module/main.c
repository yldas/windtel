/*WindTel Libraries*/
#include "DriverLibFiles/driverlib.h"
#include "WindTel_Graphic.h"

/* Standard Define Libraries */
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define TIMER_PERIOD    11718

/* Slave Address for I2C Slave */
#define SLAVE_ADDRESS       0x000C
#define NUM_OF_REC_BYTES    11

/* Variables */
const uint8_t TXData[] = {0x19};
static char RXData[NUM_OF_REC_BYTES];
static volatile uint32_t xferIndex;
static volatile bool stopSent;

// Graphic library context
Graphics_Context g_sContext;
Graphics_Rectangle rect;
float currentSpeed =0;
int cursor = 1;
int menuIndex = 1;
int on_off = 1;
int potentiometerStep = 0;

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

const Timer_A_UpModeConfig updateSpeedConfig =
{
 TIMER_A_CLOCKSOURCE_ACLK,              // ACLK Clock Source
 TIMER_A_CLOCKSOURCE_DIVIDER_1,          // ACLK/1 = 3MHz
 52334,                           // 5000 tick period
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
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &updateSpeedConfig);

    // I2C Pin Setup
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
                                                   GPIO_PIN6 + GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    // I2C is not sending any data yet
    stopSent = false;

    memset(RXData, 0x00, NUM_OF_REC_BYTES);

    /* Initializing I2C Master to SMCLK at 100khz with no autostop */
    MAP_I2C_initMaster(EUSCI_B2_BASE, &i2cConfig);

    /* Specify slave address */
    MAP_I2C_setSlaveAddress(EUSCI_B2_BASE, SLAVE_ADDRESS);

    /* Enable I2C Module to start operations */
    MAP_I2C_enableModule(EUSCI_B2_BASE);

    MAP_Interrupt_enableInterrupt(INT_EUSCIB2);

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
                nextOption(g_sContext, rect, menuIndex,cursor);
                cursor++;
                if(cursor == 6)
                    cursor = 1;
            }
            else if(menuIndex == 2){

            }
            else if(menuIndex == 4){
                nextOption(g_sContext, rect,menuIndex,cursor);
                cursor++;
                if(cursor == 4)
                    cursor = 1;
            }
        }
    }
    //Left Button
    if(P5->IFG & BIT2 && !on_off){
        if(menuIndex == 1){
            previousOption(g_sContext, rect, menuIndex,cursor);
            cursor--;
            if(cursor == 0)
                cursor = 5;
        }
        else if(menuIndex == 2){

        }
        if(menuIndex == 4){
            previousOption(g_sContext, rect,menuIndex,cursor);
            cursor--;
            if(cursor == 0)
                cursor = 3;
        }
    }

    //Confirm Button
    if(P5->IFG & BIT6 && !on_off){
        if(menuIndex == 1){
            if(cursor == 4){
                drawSpeedControlMenu(g_sContext, rect);
                cursor = 1;
                menuIndex = 4;
                /* Making sure the last transaction has been completely sent out */
                while (MAP_I2C_masterIsStopSent(EUSCI_B2_BASE));

                MAP_Interrupt_enableSleepOnIsrExit();

                /* Send start and the first byte of the transmit buffer. */
                MAP_I2C_masterSendMultiByteStart(EUSCI_B2_BASE, TXData[0]);
                Delay(1000);

                /* Sent the first byte, now we need to initiate the read */
                xferIndex = 0;
                MAP_I2C_masterReceiveStart(EUSCI_B2_BASE);
                MAP_I2C_enableInterrupt(EUSCI_B2_BASE, EUSCI_B_I2C_RECEIVE_INTERRUPT0);
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

        else
            Graphics_drawString(&g_sContext,"You reached maximum speed!           ", AUTO_STRING_LENGTH, 35,215,GRAPHICS_OPAQUE_TEXT);
    }



    //Back Button
    if(P5->IFG & BIT7 && !on_off){
        switch(menuIndex){
        case 1:
            Graphics_setFont(&g_sContext, &g_sFontCmss20b);
            menuIndex = 0;
            break;
        case 2:
            menuIndex = 0;
            break;
        case 3:
            menuIndex = 0;
            break;
        case 4:
            menuIndex = 0;
            break;
        case 5:
            //            drawStopWindFan();
            Graphics_setFont(&g_sContext, &g_sFontCmss20b);
            menuIndex = 0;
            break;
        case 6:
            Graphics_setFont(&g_sContext, &g_sFontCmss20b);
            menuIndex = 0;
            break;
        case 7:
            Graphics_setFont(&g_sContext, &g_sFontCmss20b);
            menuIndex = 0;
            break;
        }
    }

    P5->IFG = 0;
}

//void TA0_0_IRQHandler(void)
//{
//    updateWindSpeed(g_sContext,RXData);
//}

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
        if (xferIndex == NUM_OF_REC_BYTES - 2)
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
