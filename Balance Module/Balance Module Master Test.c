/*
 * Balance_Module_Master.c
 *
 *  Created on: Mar 21, 2019
 *      Author: Nelson G. Rodriguez Ortiz
 */

#include "msp.h"
#include "LCD.h"
#include "math.h"

char drag_front_weight_lb[5];      //Front force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char drag_back_weight_lb[5];       //Back force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char right_side_weight_lb[5];         //Up force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char left_side_weight_lb[5];         //Up force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char lift_weight_lb[5];         //Up force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char drag_front_weight_N[6];      //Front force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char drag_back_weight_N[6];       //Back force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char right_side_weight_N[6];         //Up force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char left_side_weight_N[6];         //Up force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)
char lift_weight_N[6];         //Up force data array (represents: 2 digit integer number, decimal point, 2 digit fraction)

//Delay function
void Delay(uint16_t msec){
    uint32_t i = 0;
    //Converts the milliseconds to seconds and uses the system's clock speed for the delay
    uint32_t time = (msec / 1000) * (48000000 / 15);

    //Empty loop for the delay
    for(i = 0; i < time; i++)
    {
        ;
    }
}

//Obtains forces results from Balance Module
void obtainForceMeasurements(void){
    EUSCI_B1->CTLW0 &= ~EUSCI_B_CTLW0_TR;   //Set to receiver mode
    EUSCI_B1->CTLW0 |= BIT1;                //START
    Delay(50);
    int i = 0;                              //Global index of the loop
    int j = 0;                              //Index to specify which data array to write on
    int k = 0;                              //Index of the location on the array
    //25 iterations for the 25 characters to receive (25 bytes)
    for(; i < 25; i++){
        Delay(50);
        while(!(EUSCI_B1->IFG & BIT0));     //Rx flag
        //Check to see if 5 characters have been written on a data array
        if(i!= 0 && i%5 == 0){
            j++;
        }
        k = i % 5;
        Delay(50);
        char temp = EUSCI_B1->RXBUF;        //Receives character and puts it on the RX buffer
        //@ is used to indicate a decimal point
        if(j == 0){
            if(temp == '@'){
                drag_front_weight_lb[k] = '.';
            }else{
                drag_front_weight_lb[k] = temp;
            }
        }else if(j == 1){
            if(temp == '@'){
                drag_back_weight_lb[k] = '.';
            }else{
                drag_back_weight_lb[k] = temp;
            }
        }else if(j == 2){
            if(temp == '@'){
                right_side_weight_lb[k] = '.';
            }else{
                right_side_weight_lb[k] = temp;
            }
        }else if(j == 3){
            if(temp == '@'){
                left_side_weight_lb[k] = '.';
            }else{
                left_side_weight_lb[k] = temp;
            }
        }else{
            if(temp == '@'){
                lift_weight_lb[k] = '.';
            }else{
                lift_weight_lb[k] = temp;
            }
        }
        Delay(50);
    }
    i = 0;
    j = 0;
    k = 0;
    //30 iterations for the 30 characters to receive (30 bytes)
    for(; i < 30; i++){
        Delay(50);
        while(!(EUSCI_B1->IFG & BIT0));     //Rx flag
        //Check to see if 5 characters have been written on a data array
        if(i!= 0 && i%6 == 0){
            j++;
        }
        k = i % 6;
        Delay(50);
        char temp = EUSCI_B1->RXBUF;        //Receives character and puts it on the RX buffer
        //@ is used to indicate a decimal point
        if(j == 0){
            if(temp == '@'){
                drag_front_weight_N[k] = '.';
            }else{
                drag_front_weight_N[k] = temp;
            }
        }else if(j == 1){
            if(temp == '@'){
                drag_back_weight_N[k] = '.';
            }else{
                drag_back_weight_N[k] = temp;
            }
        }else if(j == 2){
            if(temp == '@'){
                right_side_weight_N[k] = '.';
            }else{
                right_side_weight_N[k] = temp;
            }
        }else if(j == 3){
            if(temp == '@'){
                left_side_weight_N[k] = '.';
            }else{
                left_side_weight_N[k] = temp;
            }
        }else{
            if(temp == '@'){
                lift_weight_N[k] = '.';
            }else{
                lift_weight_N[k] = temp;
            }
        }
        Delay(50);
    }

    EUSCI_B1->CTLW0 |= BIT2;                //STOP
    Delay(50);
}

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    EUSCI_B1->CTLW0 = BIT0;                         //UCSWRST = 1b = software reset enabled
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_MST;           //Selects this micro-controller as master
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_MODE_3;        //I2C mode
    EUSCI_B1->CTLW0 |= BIT6;                        //UCSSEL0 = 01b = clk src set to ACLK
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TR;            //Sets bus to transmit
    EUSCI_B1->BRW = (uint16_t) 0x13;                //Baud rate set to 0x20 ~ 4 kilo bits per second
    P6SEL0 |= BIT4;
    P6SEL1 &= ~BIT4;
    P6SEL0 |= BIT5;
    P6SEL1 &= ~BIT5;
    EUSCI_B1->CTLW0 &= ~BIT0;                       //UCSWRST = 1b = software reset disabled
    Delay(100);
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TR;    //Set to transmitter mode
    EUSCI_B1->I2CSA |= 0x000B;              //Balance Module Slave address
    Delay(100);
    EUSCI_B1->CTLW0 |= BIT1;                //START
    Delay(750);
    while(!(EUSCI_B1->IFG & BIT1));         //Tx flag
    EUSCI_B1->TXBUF = 0x01;                 //Dummy data
    Delay(750);
    while(!(EUSCI_B1->IFG & BIT1));
    EUSCI_B1->CTLW0 |= BIT2;                //STOP
    Delay(750);
    while(!(EUSCI_B1->IFG & BIT3));         //STOP flag

    //    LCD Display initialization
    setPort(2,0x00);
    LCD_init(2,5,1,5,0,5,2);
    LCD_busy2(2,5,1,5,0,5,2);

    while(1)
    {
        obtainForceMeasurements();  //Acquires forces from Balance Module

        //Display drag front force in LCD
        clearLCD(2,5,1,5,0,5,2);
        cursorCentered(2,5,1,5,0,5,2,"Drag Fnt F");
        writeCommand(2,5,1,5,0,5,2,'n',"Drag Fnt F");
        returnToInit(2,5,1,5,0,5,2,'0');
        cursorUpDown(2,5,1,5,0,5,2,'1');
        writeCommand(2,5,1,5,0,5,2,'n',drag_front_weight_lb);
        writeCommand(2,5,1,5,0,5,2,'n',"lb ");
        writeCommand(2,5,1,5,0,5,2,'n',drag_front_weight_N);
        writeCommand(2,5,1,5,0,5,2,'n',"N");
        Delay(1000);

        //Display drag back force in LCD
        clearLCD(2,5,1,5,0,5,2);
        cursorCentered(2,5,1,5,0,5,2,"Drag Bck F");
        writeCommand(2,5,1,5,0,5,2,'n',"Drag Bck F");
        returnToInit(2,5,1,5,0,5,2,'0');
        cursorUpDown(2,5,1,5,0,5,2,'1');
        writeCommand(2,5,1,5,0,5,2,'n',drag_back_weight_lb);
        writeCommand(2,5,1,5,0,5,2,'n',"lb ");
        writeCommand(2,5,1,5,0,5,2,'n',drag_back_weight_N);
        writeCommand(2,5,1,5,0,5,2,'n',"N");
        Delay(1000);

        //Display right side force in LCD
        clearLCD(2,5,1,5,0,5,2);
        cursorCentered(2,5,1,5,0,5,2,"Right Side F");
        writeCommand(2,5,1,5,0,5,2,'n',"Right Side F");
        returnToInit(2,5,1,5,0,5,2,'0');
        cursorUpDown(2,5,1,5,0,5,2,'1');
        writeCommand(2,5,1,5,0,5,2,'n',right_side_weight_lb);
        writeCommand(2,5,1,5,0,5,2,'n',"lb ");
        writeCommand(2,5,1,5,0,5,2,'n',right_side_weight_N);
        writeCommand(2,5,1,5,0,5,2,'n',"N");
        Delay(1000);

        //Display left side force in LCD
        clearLCD(2,5,1,5,0,5,2);
        cursorCentered(2,5,1,5,0,5,2,"Left Side F");
        writeCommand(2,5,1,5,0,5,2,'n',"Left Side F");
        returnToInit(2,5,1,5,0,5,2,'0');
        cursorUpDown(2,5,1,5,0,5,2,'1');
        writeCommand(2,5,1,5,0,5,2,'n',left_side_weight_lb);
        writeCommand(2,5,1,5,0,5,2,'n',"lb ");
        writeCommand(2,5,1,5,0,5,2,'n',left_side_weight_N);
        writeCommand(2,5,1,5,0,5,2,'n',"N");
        Delay(1000);

        //Display lift force in LCD
        clearLCD(2,5,1,5,0,5,2);
        cursorCentered(2,5,1,5,0,5,2,"Lift F");
        writeCommand(2,5,1,5,0,5,2,'n',"Lift F");
        returnToInit(2,5,1,5,0,5,2,'0');
        cursorUpDown(2,5,1,5,0,5,2,'1');
        writeCommand(2,5,1,5,0,5,2,'n',lift_weight_lb);
        writeCommand(2,5,1,5,0,5,2,'n',"lb ");
        writeCommand(2,5,1,5,0,5,2,'n',lift_weight_N);
        writeCommand(2,5,1,5,0,5,2,'n',"N");
        Delay(1000);
    }
}


