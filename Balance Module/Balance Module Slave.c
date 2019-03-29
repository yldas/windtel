/*
 * Balance_Module.c
 *
 *  Created on: March 20, 2019
 *      Author: Nelson G. Rodriguez Ortiz
 */

#include "msp.h"
#include "math.h"

unsigned int ADC_value13 = 0;   //Digital code of ADC channel 13 conversion
unsigned int ADC_value12 = 0;   //Digital code of ADC channel 12 conversion
unsigned int ADC_value11 = 0;   //Digital code of ADC channel 11 conversion
unsigned int ADC_value10 = 0;   //Digital code of ADC channel 10 conversion
unsigned int ADC_value9 = 0;    //Digital code of ADC channel 9 conversion
float ADC_volt13 = 0.0; //Analog voltage obtained in ADC channel 13
float ADC_volt12 = 0.0; //Analog voltage obtained in ADC channel 12
float ADC_volt11 = 0.0; //Analog voltage obtained in ADC channel 11
float ADC_volt10 = 0.0; //Analog voltage obtained in ADC channel 10
float ADC_volt9 = 0.0;  //Analog voltage obtained in ADC channel 9
float drag_front_weight_lb = 0.0;   //Drag front weight in lb
float drag_front_force_lb = 0.0;    //Drag front force in lb
float drag_front_weight_N = 0.0;    //Drag front weight in N
float drag_front_force_N = 0.0; //Drag front force in N
float drag_back_weight_lb = 0.0;    //Drag back weight in lb
float drag_back_force_lb = 0.0; //Drag back force in lb
float drag_back_weight_N = 0.0; //Drag back weight in N
float drag_back_force_N = 0.0;  //Drag back force in N
float right_side_weight_lb = 0.0;   //Right side weight in lb
float right_side_weight_N = 0.0;    //Right side weight in N
float left_side_weight_lb = 0.0;    //Left side weight in lb
float left_side_weight_N = 0.0; //Left side weight in N
float lift_weight_lb = 0.0; //Lift weight in lb
float lift_force_lb = 0.0;  //Lift force in lb
float lift_weight_N = 0.0;  //Lift weight in N
float lift_force_N = 0.0;   //Lift force in N
float L1 = 14.605; //Distance between balance support point and drag load cell in cm
float L2 = 16.748; //Distance between balance support point and rod base in cm
float L3_base_rod = 19.288; //Height of rod base in cm
float L4 = 18.971; //Distance between balance support and lift load cell in cm
int results[20];  //results array stores the forces results. Even indexes are the integer part of the measurement
//and odd indexes are the fractional part of the measurement
int globalIndex = 0; //globalIndex is used to denote whether to put an '@' (decimal point) or not. If it's even,
//an '@' shall be written to the Master Module or not otherwise.
int conv = 0;   //Index used to iterate ADC conversions

// Delay function
void delay(int del){
    int i = 0;
    for(; i < del; i++);
}

//Stores forces results before transmitting to Master Module
void storeValues(void){
    results[0] = drag_front_weight_lb;
    results[2] = drag_back_weight_lb;
    results[4] = right_side_weight_lb;
    results[6] = left_side_weight_lb;
    results[8] = lift_weight_lb;
    results[10] = drag_front_weight_N;
    results[12] = drag_back_weight_N;
    results[14] = right_side_weight_N;
    results[16] = left_side_weight_N;
    results[18] = lift_weight_N;
    int i = 0;
    int temp1 = 0;
    int temp2 = 0;
    int integer = 0;
    float fraction1 = 0.0;
    int fraction = 0;
    float value = 0.0;
    for(; i < 10; i++){
        if(i == 0){
            value = drag_front_weight_lb;
        }else if(i == 1){
            value = drag_back_weight_lb;
        }else if(i == 2){
            value = right_side_weight_lb;
        }else if(i == 3){
            value = left_side_weight_lb;
        }else if(i == 4){
            value = lift_weight_lb;
        }else if(i == 5){
            value = drag_front_weight_N;
        }else if(i == 6){
            value = drag_back_weight_N;
        }else if(i == 7){
            value = right_side_weight_N;
        }else if(i == 8){
            value = left_side_weight_N;
        }else if(i == 9){
            value = lift_weight_N;
        }
        temp1 = i*2;
        temp2 = i*2 + 1;
        integer = results[temp1];
        fraction1 = (value - integer)*100.0;
        fraction = fraction1;
        results[temp2] = fraction;
    }
}

//Send forces results to Master Module through I2C Bus
void sendData(void){
    int i;
    int temp = 0;
    int result = 0;
    for(i = 0; i < 10; i++){
        result = results[temp];
        convertToChars(result, 2);
        temp++;
    }
    globalIndex = 0;
    i = 0;
    temp = 10;
    for(; i < 5; i++){
        result = results[temp];
        convertToChars(result, 3);
        temp++;
        result = results[temp];
        convertToChars(result, 2);
        temp++;
    }
    EUSCI_B0->CTLW0 |= BIT2;            //STOP
    delay(1500);
}

//Converts forces results (float type) to character
void convertToChars(int num, int digits){
    int temp1 = num;
    int multiple = 1;
    int i = 0;
    int count = 0;
    if(num == 0){
        for(; i < digits; i++){
            while(!(EUSCI_B0->IFG & BIT1));
            EUSCI_B0->TXBUF = '0';
        }
    }else{
        while(temp1 != 0){
            multiple *= 10;
            temp1 /= 10;
            count++;
        }
        temp1 = num;
        if(temp1 < 0){
            temp1 *= -1;
        }
        int digit;
        int j = 0;
        while(multiple > 1 || j < digits){
            if((digits - count) > j){
                while(!(EUSCI_B0->IFG & BIT1));
                EUSCI_B0->TXBUF = '0';
            }else{
                multiple/= 10;
                digit = temp1/multiple;
                if(digit == 0){
                    while(!(EUSCI_B0->IFG & BIT1));
                    EUSCI_B0->TXBUF = '0';
                }else{
                    while(!(EUSCI_B0->IFG & BIT1));
                    EUSCI_B0->TXBUF = digit+'0';
                }
                temp1 %= multiple;
            }
            j++;
        }
    }
    //Check whether to put an '@' (represents a decimal point) or not. If globalIndex is even, it will put an '@'. Otherwise it won't.
    if(globalIndex%2 == 0){
        while(!(EUSCI_B0->IFG & BIT1));
        EUSCI_B0->TXBUF = '@';
    }
    globalIndex++;
}


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    //Clock System Configuration Setup
    CS->CTL1 = CS_CTL1_DIVA__1; //ACLK/1
    CS->CLKEN = CS_CLKEN_REFOFSEL | //REFO set to 128kHz
            CS_CLKEN_ACLK_EN;

    //PORT 4 Setup
    P4->SEL0 |= BIT0;   //Set port as Analog input A13
    P4->SEL1 |= BIT0;

    P4->SEL0 |= BIT1;   //Set port as Analog input A12
    P4->SEL1 |= BIT1;

    P4->SEL0 |= BIT2;   //Set port as Analog input A11
    P4->SEL1 |= BIT2;

    P4->SEL0 |= BIT3;   //Set port as Analog input A10
    P4->SEL1 |= BIT3;

    P4->SEL0 |= BIT4;   //Set port as Analog input A9
    P4->SEL1 |= BIT4;

    //ADC Configuration Setup
    ADC14->CTL0 &= ~ADC14_CTL0_ENC; //Disable Conversion before ADC setup
    ADC14->CTL0 = ADC14_CTL0_CONSEQ_3;  //Repeat sequence of channels mode
    ADC14->CTL0 |= ADC14_CTL0_SHT0__16 | ADC14_CTL0_SHP | ADC14_CTL0_MSC | ADC14_CTL0_ON;    //Sample and Hold time setup, SAMPCON sourced from sampling timer,
    //Multiple sample conversions and ADC ON
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_13; //Channel 13 Selected and Vref+ = VCC = 3.3V, Vref- = GND
    ADC14->MCTL[1] |= ADC14_MCTLN_INCH_12; //Channel 12 Selected and Vref+ = VCC = 3.3V, Vref- = GND
    ADC14->MCTL[2] |= ADC14_MCTLN_INCH_11;    //Channel 11 Selected and Vref+ = VCC = 3.3V, Vref- = GND
    ADC14->MCTL[3] |= ADC14_MCTLN_INCH_10;    //Channel 10 Selected and Vref+ = VCC = 3.3V, Vref- = GND
    ADC14->MCTL[4] |= ADC14_MCTLN_INCH_9 | ADC14_MCTLN_EOS;    //Channel 9 Selected, End of sequence bit enable and Vref+ = VCC = 3.3V, Vref- = GND
    ADC14->CTL1 |= ADC14_CTL1_RES_3; //Resolution of ADC to 14 bits
    ADC14->IER0 |= ADC14_IER0_IE0;   //ADC Interrupt Enable

    EUSCI_B0->CTLW0 = BIT0;                             //UCSWRST = 1b = software reset enabled
    EUSCI_B0->I2COA0 |= (0x0400 + 0x8000);              //General call response and own address enable
    EUSCI_B0->I2COA0 |= 0x000B;                         //Slave address
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_MST;              //Slave
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_MODE_3;            //I2C
    EUSCI_B0->BRW = (uint16_t) 0x13;                    //BR
    P1SEL0 |= BIT6;
    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT7;
    P1SEL1 &= ~BIT7;
    EUSCI_B0->CTLW0 &= ~BIT0;                           //UCSWRST = 1b = software reset disabled
    EUSCI_B0->IE |= 0x000F;                             //Enable interrupts


//Performs 10 ADC conversions before storing results
    while(conv < 10)
    {
        ADC14->CTL0 |= ADC14_CTL0_ENC | //Enable and Start Conversion
                ADC14_CTL0_SC;
        conv++;
    }

    ADC14->CTL0 &= ~ADC14_CTL0_ENC; //Disable Conversion

    __enable_irq();

    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);
    NVIC->ISER[0] = 1 << (EUSCIB0_IRQn);

}

//ADC Module Interrupt Handler
void ADC14_IRQHandler(void)
{

    if(ADC14->IFGR0 & 0x1)
    {

        ADC_value13 = ADC14->MEM[0]; //Store first conversion
        ADC_volt13 = ((3.3*ADC_value13)/(16384.0));   //Verify the analog value of first conversion
        drag_front_weight_lb = (ADC_volt13*45)/3.3;    //Voltage to force conversion in lb with calibration values
        drag_front_force_lb = drag_front_weight_lb*(L2/L1); //Drag front force in lb
        drag_front_weight_N = drag_front_weight_lb*4.45;   //Drag front weight in N
        drag_front_force_N = drag_front_force_lb*4.45;  //Drag front force in N

        ADC_value12 = ADC14->MEM[1];    //Store second conversion
        ADC_volt12 = ((3.3*ADC_value12)/(16384.0)); //Verify the analog value of second conversion
        drag_back_weight_lb = (ADC_volt12*45)/3.3;    //Voltage to force conversion in lb with calibration values
        drag_back_force_lb = drag_back_weight_lb*(L2/L1);   //Drag back force in lb
        drag_back_weight_N = drag_back_weight_lb*4.45;   //Drag back weight in N
        drag_back_force_N = drag_back_force_lb*4.45;    //Drag back force in N

        ADC_value11 = ADC14->MEM[2];    //Store third conversion
        ADC_volt11 = ((3.3*ADC_value11)/(16384.0)); //Verify the analog value of third conversion
        right_side_weight_lb = (ADC_volt11*45)/3.3;    //Voltage to force conversion in lb with calibration values
        right_side_weight_N = right_side_weight_lb*4.45;   //Right side force in N

        ADC_value10 = ADC14->MEM[3];    //Store fourth conversion
        ADC_volt10 = ((3.3*ADC_value10)/(16384.0)); //Verify the analog value of fourth conversion
        left_side_weight_lb = (ADC_volt10*45)/3.3;    //Voltage to force conversion in lb with calibration values
        left_side_weight_N = left_side_weight_lb*4.45;   //Left side force in N

        ADC_value9 = ADC14->MEM[4];    //Store fifth conversion
        ADC_volt9 = ((3.3*ADC_value9)/(16384.0)); //Verify the analog value of third conversion
        lift_weight_lb = (ADC_volt9*45)/3.3;    //Voltage to force conversion in lb with calibration values
        lift_force_lb = lift_force_lb*(L4/L3_base_rod); //Lift force in lb
        lift_weight_N = lift_weight_lb*4.45;   //Lift weight in N
        lift_force_N = lift_force_lb*4.45;  //Lift force in N

        ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0;   //Clear ADC IFG

    }

}

void EUSCIB0_IRQHandler(void){
    //Checks the RX buffer to see if the Master Module has sent a command
    if(EUSCI_B0->IFG & BIT0){
        if(EUSCI_B0->RXBUF == 0xFF){
            SYSCTL->REBOOT_CTL = 0x6901;        //Software Reset
        }
    }
    //Checks the TX buffer to see if the Master Module is ready to read the data acquisition from the Balance Module
    if(EUSCI_B0->IFG & BIT1){
        storeValues();
        sendData();
    }
    EUSCI_B0->IFG = 0;                          //Clears the interrupt flag
}


