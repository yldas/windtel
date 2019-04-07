/*
 * Balance_Module.c
 *
 *  Created on: April 7, 2019
 *      Author: Nelson G. Rodriguez Ortiz
 */

#include "msp.h"
#include "math.h"

unsigned int ADC_value14 = 0;    //Digital code of ADC channel 14 conversion
unsigned int ADC_value13 = 0;   //Digital code of ADC channel 13 conversion
unsigned int ADC_value12 = 0;   //Digital code of ADC channel 12 conversion
unsigned int ADC_value11 = 0;   //Digital code of ADC channel 11 conversion
unsigned int ADC_value10 = 0;   //Digital code of ADC channel 10 conversion
unsigned int ADC_value9 = 0;    //Digital code of ADC channel 9 conversion
unsigned int ADC_value8 = 0;    //Digital code of ADC channel 8 conversion
unsigned int ADC_value7 = 0;    //Digital code of ADC channel 7 conversion
unsigned int ADC_value6 = 0;    //Digital code of ADC channel 6 conversion
unsigned int ADC_value5 = 0;    //Digital code of ADC channel 5 conversion
unsigned int ADC_value4 = 0;    //Digital code of ADC channel 4 conversion
unsigned int ADC_value3 = 0;    //Digital code of ADC channel 3 conversion
unsigned int ADC_value2 = 0;    //Digital code of ADC channel 2 conversion
unsigned int ADC_value1 = 0;    //Digital code of ADC channel 1 conversion
unsigned int ADC_value0 = 0;    //Digital code of ADC channel 0 conversion
float ADC_volt14 = 0.0;  //Analog voltage obtained in ADC channel 14
float ADC_volt13 = 0.0; //Analog voltage obtained in ADC channel 13
float ADC_volt12 = 0.0; //Analog voltage obtained in ADC channel 12
float ADC_volt11 = 0.0; //Analog voltage obtained in ADC channel 11
float ADC_volt10 = 0.0; //Analog voltage obtained in ADC channel 10
float ADC_volt9 = 0.0;  //Analog voltage obtained in ADC channel 9
float ADC_volt8 = 0.0;  //Analog voltage obtained in ADC channel 8
float ADC_volt7 = 0.0;  //Analog voltage obtained in ADC channel 7
float ADC_volt6 = 0.0;  //Analog voltage obtained in ADC channel 6
float ADC_volt5 = 0.0;  //Analog voltage obtained in ADC channel 5
float ADC_volt4 = 0.0;  //Analog voltage obtained in ADC channel 4
float ADC_volt3 = 0.0;  //Analog voltage obtained in ADC channel 3
float ADC_volt2 = 0.0;  //Analog voltage obtained in ADC channel 2
float ADC_volt1 = 0.0;  //Analog voltage obtained in ADC channel 1
float ADC_volt0 = 0.0;  //Analog voltage obtained in ADC channel 0
float ADC_volt_dragf_ave = 0.0; //Average voltage obtained in drag front load cell
float ADC_volt_dragb_ave = 0.0; //Average voltage obtained in drag back load cell
float ADC_volt_right_ave = 0.0; //Average voltage obtained in right side load cell
float ADC_volt_left_ave = 0.0;  //Average voltage obtained in left side load cell
float ADC_volt_lift_ave = 0.0;  //Average voltage obtained in lift load cell
float dragf_error_factor = 0.0; //Error factor in drag front load cell
float dragb_error_factor = 0.0; //Error factor in drag back load cell
float right_error_factor = 0.0; //Error factor in right side load cell
float left_error_factor = 0.0;  //Error factor in left side load cell
float lift_error_factor = 0.0;  //Error factor in lift load cell
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
int n_dragf = 0;    //Rate of change between difference of drag front conditioned output voltage and 2.54V, and 0.01 used for error correction
int n_dragb = 0;    //Rate of change between difference of drag back conditioned output voltage and 2.54V, and 0.01 used for error correction
int n_right = 0;    //Rate of change between difference of right side conditioned output voltage and 2.54V, and 0.01 used for error correction
int n_left = 0; //Rate of change between difference of left side conditioned output voltage and 2.54V, and 0.01 used for error correction
int n_lift = 0; //Rate of change between difference of lift conditioned output voltage and 2.54V, and 0.01 used for error correction

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
    CS->CTL1 = CS_CTL1_DIVS_0; //SMCLK/1
    CS->CLKEN = CS_CLKEN_REFOFSEL | //REFO set to 24MHz
            CS_CLKEN_ACLK_EN;

    //PORT 4 Setup
    P4->SEL0 |= BIT0;   //Set pin 4.0 as Analog input A13
    P4->SEL1 |= BIT0;

    P4->SEL0 |= BIT1;   //Set pin 4.1 as Analog input A12
    P4->SEL1 |= BIT1;

    P4->SEL0 |= BIT2;   //Set pin 4.2 as Analog input A11
    P4->SEL1 |= BIT2;

    P4->SEL0 |= BIT3;   //Set pin 4.3 as Analog input A10
    P4->SEL1 |= BIT3;

    P4->SEL0 |= BIT4;   //Set pin 4.4 as Analog input A9
    P4->SEL1 |= BIT4;

    P4->SEL0 |= BIT5;   //Set pin 4.5 as Analog input A8
    P4->SEL1 |= BIT5;

    P4->SEL0 |= BIT6;   //Set pin 4.6 as Analog input A7
    P4->SEL1 |= BIT6;

    P4->SEL0 |= BIT7;   //Set pin 4.7 as Analog input A6
    P4->SEL1 |= BIT7;

    //PORT 5 Setup
    P5->SEL0 |= BIT0;   //Set pin 5.0 as Analog input A5
    P5->SEL1 |= BIT0;

    P5->SEL0 |= BIT1;   //Set pin 5.1 as Analog input A4
    P5->SEL1 |= BIT1;

    P5->SEL0 |= BIT2;   //Set pin 5.2 as Analog input A3
    P5->SEL1 |= BIT2;

    P5->SEL0 |= BIT3;   //Set pin 5.3 as Analog input A2
    P5->SEL1 |= BIT3;

    P5->SEL0 |= BIT4;   //Set pin 5.4 as Analog input A1
    P5->SEL1 |= BIT4;

    P5->SEL0 |= BIT5;   //Set pin 5.5 as Analog input A0
    P5->SEL1 |= BIT5;

    P5->SEL0 |= BIT6;   //Set pin 5.6 as external VeRef+
    P5->SEL1 |= BIT6;

    P5->SEL0 |= BIT7;   //Set pin 5.7 as external VeRef-
    P5->SEL1 |= BIT7;

    //Port 6 Setup
    P6->SEL0 |= BIT1;   //Set pin 6.1 as Analog input A14
    P6->SEL1 |= BIT1;

    //ADC Configuration Setup
    ADC14->CTL0 &= ~ADC14_CTL0_ENC; //Disable Conversion before ADC setup
    ADC14->CTL0 = ADC14_CTL0_CONSEQ_3;  //Repeat sequence of channels mode
    ADC14->CTL0 |= ADC14_CTL0_SHT0__128 | ADC14_CTL0_SHP | ADC14_CTL0_MSC | ADC14_CTL0_ON;    //Sample and Hold time setup, SAMPCON sourced
    //from sampling timer, Multiple sample conversions and ADC ON
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_13 | ADC14_MCTLN_VRSEL_14; //Channel 13 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[1] |= ADC14_MCTLN_INCH_12 | ADC14_MCTLN_VRSEL_14; //Channel 12 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[2] |= ADC14_MCTLN_INCH_11 | ADC14_MCTLN_VRSEL_14;    //Channel 11 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[3] |= ADC14_MCTLN_INCH_10 | ADC14_MCTLN_VRSEL_14;    //Channel 10 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[4] |= ADC14_MCTLN_INCH_9 | ADC14_MCTLN_VRSEL_14;    //Channel 9 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[5] |= ADC14_MCTLN_INCH_8 | ADC14_MCTLN_VRSEL_14;    //Channel 8 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[6] |= ADC14_MCTLN_INCH_7 | ADC14_MCTLN_VRSEL_14;    //Channel 7 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[7] |= ADC14_MCTLN_INCH_6 | ADC14_MCTLN_VRSEL_14;    //Channel 6 selected  and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[8] |= ADC14_MCTLN_INCH_5 | ADC14_MCTLN_VRSEL_14;    //Channel 5 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[9] |= ADC14_MCTLN_INCH_4 | ADC14_MCTLN_VRSEL_14;    //Channel 4 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[10] |= ADC14_MCTLN_INCH_3 | ADC14_MCTLN_VRSEL_14;    //Channel 3 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[11] |= ADC14_MCTLN_INCH_2 | ADC14_MCTLN_VRSEL_14;    //Channel 2 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[12] |= ADC14_MCTLN_INCH_1 | ADC14_MCTLN_VRSEL_14;    //Channel 1 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[13] |= ADC14_MCTLN_INCH_0 | ADC14_MCTLN_VRSEL_14;    //Channel 0 selected and Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
    ADC14->MCTL[14] |= ADC14_MCTLN_INCH_14 | ADC14_MCTLN_VRSEL_14 | ADC14_MCTLN_EOS;    //Channel 14 selected, End of sequence bit enable and
    //Vref+ = VeRef+ = 3.3V, Vref- = VeRef- = GND
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


    //Performs 1000 ADC conversions before storing results
    while(conv < 1000)
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

        //Drag front load cell conditioned output voltage acquisition
        ADC_value13 = ADC14->MEM[0]; //Stores first conversion
        ADC_volt13 = ((3.3*ADC_value13)/(16384.0));   //Obtains first sample of drag front load cell conditioned output voltage
        ADC_value12 = ADC14->MEM[1];    //Stores second conversion
        ADC_volt12 = ((3.3*ADC_value12)/(16384.0)); //Obtains second sample of drag front load cell conditioned output voltage
        ADC_value11 = ADC14->MEM[2];    //Stores third conversion
        ADC_volt11 = ((3.3*ADC_value11)/(16384.0)); //Obtains third sample of drag front load cell conditioned output voltage
        ADC_volt_dragf_ave = (ADC_volt13 + ADC_volt12 + ADC_volt11)/3;    //Calculates the average of drag front load cell conditioned output
        //voltage

        //Analog voltage to drag front force conversion
        if(ADC_volt_dragf_ave >= 2.50 && ADC_volt_dragf_ave < 2.535)    //No weight in load cell
        {
            drag_front_weight_lb = 0.00;
        }
        else if(ADC_volt_dragf_ave >= 2.545 && ADC_volt_dragf_ave <= 3.3)   //Weight in load cell
        {
            //Error correction factor when weight is greater or equal to 5lb
            n_dragf = (ADC_volt_dragf_ave - 2.54)/0.01;
            dragf_error_factor = 0.0004 + (n_dragf-1)*0.00015;

            //Drag front weight conversion using INA333 gain, load cells Voltage (mV) vs Weight (lb) transfer characteristic and
            //error correction factor
            drag_front_weight_lb = (((ADC_volt_dragf_ave-2.50)/(1+100/1.4))+dragf_error_factor)*(45/0.01);
        }
        else if(ADC_volt_dragf_ave > 3.3) //When maximum weight (45lb) is exceeded
        {
            drag_front_weight_lb = 45.00;
        }
        else    //Used when weight in load cell is between 1lb and 5lb
        {
            //Drag front weight conversion using INA333 gain and load cells Voltage (mV) vs Weight (lb) transfer characteristic, no error
            //correction factor is needed (error doesn't affect measurement accuracy)
            drag_front_weight_lb = ((ADC_volt_dragf_ave-2.50)/(1+100/1.4))*(45/0.01);
        }
        drag_front_force_lb = drag_front_weight_lb*(L2/L1); //Calculates drag front force in lb
        drag_front_weight_N = drag_front_weight_lb*4.45;   //Calculates drag front weight in N
        drag_front_force_N = drag_front_force_lb*4.45;  //Calculates drag front force in N

        //Drag back load cell conditioned output voltage acquisition
        ADC_value10 = ADC14->MEM[3];    //Stores first conversion
        ADC_volt10 = ((3.3*ADC_value10)/(16384.0)); //Obtains first sample of drag back load cell conditioned output voltage
        ADC_value9 = ADC14->MEM[4];    //Stores second conversion
        ADC_volt9 = ((3.3*ADC_value9)/(16384.0)); //Obtains second sample of drag back load cell conditioned output voltage
        ADC_value8 = ADC14->MEM[5];    //Stores third conversion
        ADC_volt8 = ((3.3*ADC_value8)/(16384.0)); //Obtains third sample of drag back load cell conditioned output voltage
        ADC_volt_dragb_ave = (ADC_volt10 + ADC_volt9 + ADC_volt8)/3;    //Calculates the average of drag back load cell conditioned output
        //voltage

        //Analog voltage to drag back force conversion
        if(ADC_volt_dragb_ave >= 2.50 && ADC_volt_dragb_ave < 2.535)    //No weight in load cell
        {
            drag_back_weight_lb = 0.00;
        }
        else if(ADC_volt_dragb_ave >= 2.545 && ADC_volt_dragb_ave <= 3.3)   //Weight in load cell
        {
            //Error correction factor when weight is greater or equal to 5lb
            n_dragb = (ADC_volt_dragb_ave - 2.54)/0.01;
            dragb_error_factor = 0.0004 + (n_dragb-1)*0.00015;

            //Drag back weight conversion using INA333 gain, load cells Voltage (mV) vs Weight (lb) transfer characteristic and
            //error correction factor
            drag_back_weight_lb = (((ADC_volt_dragb_ave-2.50)/(1+100/1.4))+dragb_error_factor)*(45/0.01);
        }
        else if(ADC_volt_dragb_ave > 3.3) //When maximum weight (45lb) is exceeded
        {
            drag_back_weight_lb = 45.00;
        }
        else    //Used when weight in load cell is between 1lb and 5lb
        {
            //Drag back weight conversion using INA333 gain and load cells Voltage (mV) vs Weight (lb) transfer characteristic, no error
            //correction factor is needed (error doesn't affect measurement accuracy)
            drag_back_weight_lb = ((ADC_volt_dragb_ave-2.50)/(1+100/1.4))*(45/0.01);
        }
        drag_back_force_lb = drag_back_weight_lb*(L2/L1);   //Calculates drag back force in lb
        drag_back_weight_N = drag_back_weight_lb*4.45;   //Calculates drag back weight in N
        drag_back_force_N = drag_back_force_lb*4.45;    //Calculates drag back force in N

        //Right side load cell conditioned output voltage acquisition
        ADC_value7 = ADC14->MEM[6];    //Stores first conversion
        ADC_volt7 = ((3.3*ADC_value11)/(16384.0)); //Obtains first sample of right side load cell conditioned output voltage
        ADC_value6 = ADC14->MEM[7];    //Stores second conversion
        ADC_volt6 = ((3.3*ADC_value6)/(16384.0)); //Obtains second sample of right side load cell conditioned output voltage
        ADC_value5 = ADC14->MEM[8];    //Stores third conversion
        ADC_volt5 = ((3.3*ADC_value5)/(16384.0)); //Obtains third sample of right side load cell conditioned output voltage
        ADC_volt_right_ave = (ADC_volt7 + ADC_volt6 + ADC_volt5)/3;    //Calculates the average of right side load cell conditioned output
        //voltage

        //Analog voltage to right side force conversion
        if(ADC_volt_right_ave >= 2.50 && ADC_volt_right_ave < 2.535)    //No weight in load cell
        {
            right_side_weight_lb = 0.00;
        }
        else if(ADC_volt_right_ave >= 2.545 && ADC_volt_right_ave <= 3.3)   //Weight in load cell
        {
            //Error correction factor when weight is greater or equal to 5lb
            n_right = (ADC_volt_right_ave - 2.54)/0.01;
            right_error_factor = 0.0004 + (n_right-1)*0.00015;

            //Right side force conversion using INA333 gain, load cells Voltage (mV) vs Weight (lb) transfer characteristic and
            //error correction factor
            right_side_weight_lb = (((ADC_volt_right_ave-2.50)/(1+100/1.4))+right_error_factor)*(45/0.01);
        }
        else if(ADC_volt_right_ave > 3.3) //When maximum weight (45lb) is exceeded
        {
            right_side_weight_lb = 45.00;
        }
        else    //Used when weight in load cell is between 1lb and 5lb
        {
            //Right side force conversion using INA333 gain and load cells Voltage (mV) vs Weight (lb) transfer characteristic, no error
            //correction factor is needed (error doesn't affect measurement accuracy)
            right_side_weight_lb = ((ADC_volt_right_ave-2.50)/(1+100/1.4))*(45/0.01);
        }
        right_side_weight_N = right_side_weight_lb*4.45;   //Calculates right side force in N

        //Left side load cell conditioned output voltage acquisition
        ADC_value4 = ADC14->MEM[9];    //Stores first conversion
        ADC_volt4 = ((3.3*ADC_value4)/(16384.0)); //Obtains first sample of left side load cell conditioned output voltage
        ADC_value3 = ADC14->MEM[10];    //Stores second conversion
        ADC_volt3 = ((3.3*ADC_value3)/(16384.0)); //Obtains second sample of left side load cell conditioned output voltage
        ADC_value2 = ADC14->MEM[11];    //Stores third conversion
        ADC_volt2 = ((3.3*ADC_value2)/(16384.0)); //Obtains third sample of left side load cell conditioned output voltage
        ADC_volt_left_ave = (ADC_volt4 + ADC_volt3 + ADC_volt2)/3;  //Calculates the average of left side load cell conditioned output
        //voltage

        //Analog voltage to left side force conversion
        if(ADC_volt_left_ave >= 2.50 && ADC_volt_left_ave < 2.535)    //No weight in load cell
        {
            left_side_weight_lb = 0.00;
        }
        else if(ADC_volt_left_ave >= 2.545 && ADC_volt_left_ave <= 3.3)   //Weight in load cell
        {
            //Error correction factor when weight is greater or equal to 5lb
            n_left = (ADC_volt_left_ave - 2.54)/0.01;
            left_error_factor = 0.0004 + (n_left-1)*0.00015;

            //Left side force conversion using INA333 gain, load cells Voltage (mV) vs Weight (lb) transfer characteristic and
            //error correction factor
            left_side_weight_lb = (((ADC_volt_left_ave-2.50)/(1+100/1.4))+left_error_factor)*(45/0.01);
        }
        else if(ADC_volt_left_ave > 3.3) //When maximum weight (45lb) is exceeded
        {
            left_side_weight_lb = 45.00;
        }
        else    //Used when weight in load cell is between 1lb and 5lb
        {
            //Left side force conversion using INA333 gain and load cells Voltage (mV) vs Weight (lb) transfer characteristic, no error
            //correction factor is needed (error doesn't affect measurement accuracy)
            left_side_weight_lb = ((ADC_volt_left_ave-2.50)/(1+100/1.4))*(45/0.01);
        }
        left_side_weight_N = left_side_weight_lb*4.45;   //Calculates left side force in N

        //Lift load cell conditioned output voltage acquisition
        ADC_value1 = ADC14->MEM[12];    //Store first conversion
        ADC_volt1 = ((3.3*ADC_value1)/(16384.0)); //Obtains first sample of lift load cell conditioned output voltage
        ADC_value0 = ADC14->MEM[13];    //Store second conversion
        ADC_volt0 = ((3.3*ADC_value0)/(16384.0)); //Obtains second sample of lift load cell conditioned output voltage
        ADC_value14 = ADC14->MEM[14];    //Store third conversion
        ADC_volt14 = ((3.3*ADC_value14)/(16384.0)); //Obtains third sample of lift load cell conditioned output voltage
        ADC_volt_lift_ave = (ADC_volt1 + ADC_volt0 + ADC_volt14)/3;  //Calculates the average of lift load cell conditioned output
        //voltage

        //Analog voltage to lift force conversion
        if(ADC_volt_lift_ave >= 2.50 && ADC_volt_lift_ave < 2.535)    //No weight in load cell
        {
            lift_weight_lb = 0.00;
        }
        else if(ADC_volt_lift_ave >= 2.545 && ADC_volt_lift_ave <= 3.3)   //Weight in load cell
        {
            //Error correction factor when weight is greater or equal to 5lb
            n_lift = (ADC_volt_lift_ave - 2.54)/0.01;
            lift_error_factor = 0.0004 + (n_lift-1)*0.00015;

            //Lift weight conversion using INA333 gain, load cells Voltage (mV) vs Weight (lb) transfer characteristic and
            //error correction factor
            lift_weight_lb = (((ADC_volt_lift_ave-2.50)/(1+100/1.4))+lift_error_factor)*(45/0.01);
        }
        else if(ADC_volt_lift_ave > 3.3) //When maximum weight (45lb) is exceeded
        {
            lift_weight_lb = 45.00;
        }
        else    //Used when weight in load cell is between 1lb and 5lb
        {
            //Lift weight conversion using INA333 gain and load cells Voltage (mV) vs Weight (lb) transfer characteristic, no error
            //correction factor is needed (error doesn't affect measurement accuracy)
            lift_weight_lb = ((ADC_volt_lift_ave-2.50)/(1+100/1.4))*(45/0.01);
        }
        lift_force_lb = lift_force_lb*(L4/L3_base_rod); //Calculates lift force in lb
        lift_weight_N = lift_weight_lb*4.45;   //Calculates lift weight in N
        lift_force_N = lift_force_lb*4.45;  //Calculates lift force in N

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

