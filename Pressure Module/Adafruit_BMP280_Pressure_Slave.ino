/*
                        Pressure Module Slave Code
 Pressure Module Slave Explanation
 This code will belong to the Pressure Module Slaves that will be directly 
 connected to the Master Module of the system. The Pressure Module Slave will
 belong to an I2C bus that will be shared with other Pressure Module Slaves, 
 having the main Pressure Module Master as its Master. This Pressure Module is
 designed to hold up to 16 barometric pressure sensors connected to it and will
 then send the data through the I2C bus to the Pressure Module Master. 

 Pressure Module Slave Design Constraints
 The Pressure Module Slave can support up to 16 barometric pressure sensors
 using the current Printed Circuit Board (PCB) design. In order to increase the 
 number of sensors, another PCB with an MSP432P401R must be added to this module 
 via an ethernet cable. Several variables will need to be modified in order for
 the addition of other Pressure Modules be valid and acceptable. Please remember
 to use the Pressure Module Slave code for the Pressure Modules to be added to the
 I2C bus and upload the code to their MSP432P401R.

 Pressure Module Slave Wiring
 When connecting the barometric pressure sensors to the PCB, please check that
 the jumper connections are correct beforehand to prevent any possible internal
 damage to the pressure sensor device, as well as to prevent data adquisition
 error, since it won't acquire the proper pressure measurement if not connected 
 correctly. Make sure that each jumper are connected between the barometric
 pressure sensor and the PCB with the correct label names (e.g. VIN to VIN, 
 SCK to SCLK, etc.).
 
 Adafruit Industries Supportability
 These barometric pressure sensors are supported by Adafruit Industries, which means that the
 configuration of these pressure sensors are explained in their datasheet and can be done through
 the libraries provided by the industry. 
 */

/* Libraries used for the source code. */
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_BMP280.h"
#include <msp.h>

/* Labels for the pins to use and their respective ports. */
#define BMP_SCK  (32)       //SPI Clock source - P3.5
#define BMP_MISO (31)       //SPI Master In Slave Out - P3.7
#define BMP_MOSI (11)       //SPI Master Out Slave In - P3.6

#define BMP_CS1  (75)       //Chip Select for BMP1 - P2.0
#define BMP_CS2  (76)       //Chip Select for BMP2 - P2.1
#define BMP_CS3  (77)       //Chip Select for BMP3 - P2.2
#define BMP_CS4  (34)       //Chip Select for BMP4 - P2.3
#define BMP_CS5  (38)       //Chip Select for BMP5 - P2.4
#define BMP_CS6  (19)       //Chip Select for BMP6 - P2.5
#define BMP_CS7  (39)       //Chip Select for BMP7 - P2.6
#define BMP_CS8  (40)       //Chip Select for BMP8 - P2.7
#define BMP_CS9  (24)       //Chip Select for BMP9 - P4.0
#define BMP_CS10 (5)        //Chip Select for BMP10 - P4.1
#define BMP_CS11 (12)       //Chip Select for BMP11 - P5.2
#define BMP_CS12 (6)        //Chip Select for BMP12 - P4.3
#define BMP_CS13 (26)       //Chip Select for BMP13 - P4.4
#define BMP_CS14 (27)       //Chip Select for BMP14 - P4.5
#define BMP_CS15 (8)        //Chip Select for BMP15 - P4.6
#define BMP_CS16 (28)       //Chip Select for BMP16 - P4.7

/* Variable definitions and BMP280 pressure sensors initialized. */
int begin_bool = 0;                                                    //For data acquisition purposes.
int bool2 = 0;
const int results_capacity = 3;
float results[results_capacity];                                       //Array where the results will be stored in type float.
int results_index = 0;
const int results_for_transmission_capacity = results_capacity*9;      //Indicates the capacity for the bytes to be transmitted to the Master
                                                                       //Module. The total maximum capacity for transmission will be 16*9 = 144.
char results_for_transmission[results_for_transmission_capacity];      //Results in type char for transmission to Master Module.
int results_for_transmission_index = 0;                                //Index used to store the char results.

Adafruit_BMP280 bmp1(BMP_CS1, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 1
Adafruit_BMP280 bmp2(BMP_CS2, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 2
Adafruit_BMP280 bmp3(BMP_CS3, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 3
Adafruit_BMP280 bmp4(BMP_CS4, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 4
Adafruit_BMP280 bmp5(BMP_CS5, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 5
Adafruit_BMP280 bmp6(BMP_CS6, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 6
Adafruit_BMP280 bmp7(BMP_CS7, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 7
Adafruit_BMP280 bmp8(BMP_CS8, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 8
Adafruit_BMP280 bmp9(BMP_CS9, BMP_MOSI, BMP_MISO,  BMP_SCK);           //BMP280 sensor 9
Adafruit_BMP280 bmp10(BMP_CS10, BMP_MOSI, BMP_MISO,  BMP_SCK);         //BMP280 sensor 10
Adafruit_BMP280 bmp11(BMP_CS11, BMP_MOSI, BMP_MISO,  BMP_SCK);         //BMP280 sensor 11
Adafruit_BMP280 bmp12(BMP_CS12, BMP_MOSI, BMP_MISO,  BMP_SCK);         //BMP280 sensor 12
Adafruit_BMP280 bmp13(BMP_CS13, BMP_MOSI, BMP_MISO,  BMP_SCK);         //BMP280 sensor 13
Adafruit_BMP280 bmp14(BMP_CS14, BMP_MOSI, BMP_MISO,  BMP_SCK);         //BMP280 sensor 14
Adafruit_BMP280 bmp15(BMP_CS15, BMP_MOSI, BMP_MISO,  BMP_SCK);         //BMP280 sensor 15
Adafruit_BMP280 bmp16(BMP_CS16, BMP_MOSI, BMP_MISO,  BMP_SCK);         //BMP280 sensor 16

/* 
 The setup function is a default function in Energia IDE that is the first function to execute. 
 Here, the baud rate is set to 9600 bits per second and the interrupts for the I2C communication
 is initialized. 
*/
void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  CS->CTL1 |= (uint32_t) 0x00000200;              //CTL1[10:8]=SELA=010b - ACLK source set to REFOCLK
  CS->CTL1 |= CS_CTL1_DIVA__32;
  CS->CLKEN = CS_CLKEN_REFOFSEL |                 //REFO set to 128kHz
          CS_CLKEN_ACLK_EN;
  init();
  __enable_irq();
  NVIC->ISER[0] = 1 << (EUSCIB1_IRQn);
}

/* setSampling will configure the sensors with the desired settings and data measurement accuracy. */
void setSampling(Adafruit_BMP280 bmp){
    /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X1,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X4,     /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

/* convertToF function will convert the parameter celsius to the equivalent temperature in Farenheit. */
float convertToF(float celsius){
  return celsius*1.8 + 32.0;
}

//Initiates the I2C communication with the Master Module
void init(){
    EUSCI_B1->CTLW0 = BIT0;                        //UCSWRST = 1b = software reset enabled
    EUSCI_B1->I2COA0 |= (0x0400 + 0x8000);         //General call response and own address enable
    EUSCI_B1->I2COA0 |= 0x000A;                    //Slave address
    EUSCI_B1->CTLW0 &= ~EUSCI_B_CTLW0_MST;         //Slave
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_MODE_3;       //I2C
    EUSCI_B1->BRW = (uint16_t) 0x20;               //BR
    P6SEL0 |= BIT4;
    P6SEL1 &= ~BIT4;
    P6SEL0 |= BIT5;
    P6SEL1 &= ~BIT5;
    EUSCI_B1->CTLW0 &= ~BIT0;                      //UCSWRST = 1b = software reset disabled
    EUSCI_B1->IE |= 0x000F;                        //Enable interrupts
}

//Converts the integer parameter num to a string, where parameter digits dictate the amount of digits it has
void convertToChars(int num, int digits){
    int temp1 = num;
    int multiple = 1;
    int i = 0;
    int count = 0;
    if(num == 0){
        for(; i < digits; i++){
              results_for_transmission[results_for_transmission_index] = '0';
              results_for_transmission_index++;
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
                  results_for_transmission[results_for_transmission_index] = '0';
                  results_for_transmission_index++;
            }else{
                multiple/= 10;
                digit = temp1/multiple;
                if(digit == 0){
                      results_for_transmission[results_for_transmission_index] = '0';
                      results_for_transmission_index++;
                }else{
                      results_for_transmission[results_for_transmission_index] = digit+'0';
                      results_for_transmission_index++;
                }
                temp1 %= multiple;
            }
            j++;
        }
    }
}

/* Converts a float number to a char array. */
void convertFloatToChars(float number){
  int integer = number;
  float temp = number;
  temp -= integer;
  temp *= 100;
  int fraction = temp;
  convertToChars(integer, 6);
  results_for_transmission[results_for_transmission_index] = '@';
  results_for_transmission_index++;
  convertToChars(fraction, 2);
}

/* This function will initialize the SPI communication with the pressure sensors, configure each sensor, as well as obtain their data and send
it to the Master Module */
void readDataFunction(char sensor){
  switch(sensor){
    case 0x01:
      if(!begin_bool){
        begin_bool = 1;
        bmp1.begin();
        setSampling(bmp1);
        bmp1.readTemperature();
        bmp1.readPressure();
      }
      bmp1.begin();
      setSampling(bmp1);
      results[results_index] = bmp1.readPressure();
      convertFloatToChars(results[results_index]);
      
    case 0x02:
      if(!begin_bool){
        begin_bool = 1;
        bmp2.begin();
        setSampling(bmp2);
        bmp2.readTemperature();
        bmp2.readPressure();
      }
      bmp2.begin();
      setSampling(bmp2);
      results[results_index] = bmp2.readPressure();
      convertFloatToChars(results[results_index]);

   case 0x03:
      if(!begin_bool){
        begin_bool = 1;
        bmp3.begin();
        setSampling(bmp3);
        bmp3.readTemperature();
        bmp3.readPressure();
      }
      bmp3.begin();
      setSampling(bmp3);
      results[results_index] = bmp3.readPressure();
      convertFloatToChars(results[results_index]);
      
    case 0x04:
      if(!begin_bool){
        begin_bool = 1;
        bmp4.begin();
        setSampling(bmp4);
        bmp4.readTemperature();
        bmp4.readPressure();
      }
      bmp4.begin();
      setSampling(bmp4);
      results[results_index] = bmp4.readPressure();
      convertFloatToChars(results[results_index]);

   case 0x05:
      if(!begin_bool){
        begin_bool = 1;
        bmp5.begin();
        setSampling(bmp5);
        bmp5.readTemperature();
        bmp5.readPressure();
      }
      bmp5.begin();
      setSampling(bmp5);
      results[results_index] = bmp5.readPressure();
      convertFloatToChars(results[results_index]);
      
    case 0x06:
      if(!begin_bool){
        begin_bool = 1;
        bmp6.begin();
        setSampling(bmp6);
        bmp6.readTemperature();
        bmp6.readPressure();
      }
      bmp6.begin();
      setSampling(bmp6);
      results[results_index] = bmp6.readPressure();
      convertFloatToChars(results[results_index]);

   case 0x07:
      if(!begin_bool){
        begin_bool = 1;
        bmp7.begin();
        setSampling(bmp7);
        bmp7.readTemperature();
        bmp7.readPressure();
      }
      bmp7.begin();
      setSampling(bmp7);
      results[results_index] = bmp7.readPressure();
      convertFloatToChars(results[results_index]);
      
    case 0x08:
      if(!begin_bool){
        begin_bool = 1;
        bmp8.begin();
        setSampling(bmp8);
        bmp8.readTemperature();
        bmp8.readPressure();
      }
      bmp8.begin();
      setSampling(bmp8);
      results[results_index] = bmp8.readPressure();
      convertFloatToChars(results[results_index]);
  }
}

void sendData(void){
  int i = 0;
  for(i; i < results_for_transmission_index; i++){
    while(!(EUSCI_B1->IFG & BIT1));
    EUSCI_B1->TXBUF = results_for_transmission[i];
    delay(50);
  }
  EUSCI_B1->CTLW0 |= BIT2;                //STOP
}

/* I2C interrupt handler. The Pressure Module will read the command from the Master Module, and the Pressure Module will proceed to execute
the instructed command. */
void EUSCIB1_IRQHandler(void){
  Serial.println("In");
    //Checks the RX buffer to see if the Master Module has sent a command
    if(EUSCI_B1->IFG & BIT0){
//      Serial.println("Rx flag...");
        while(!(EUSCI_B1->IFG & BIT0));     //Rx flag
        delay(50);
        char x = EUSCI_B1->RXBUF;
//        Serial.println(x);
        //Softreset command
        if(x == 0xFF){
            SYSCTL->REBOOT_CTL = 0x6901;    //Software Reset
        //Acquire measurements from Pressure Module Slave(s) command
//        }
//        else if(x == 0x55){
//          char y = EUSCI_B1->RXBUF;
//          int i =0;
//          for(i; i < y; i++){
////            results_next[i] = EUSCI_B1->RXBUF;
//          }
        //Acquire measurements from this Pressure Module command
        }else{
            char num_sensors = x;
            int i = 0;
            for(i; i < num_sensors; i++){
              delay(50);
              x = EUSCI_B1->RXBUF;
              readDataFunction(x);
            }
//            if(data_index == 0){
////                num_sensors = data[0];
////                numPackets = num_sensors;
////                numPackets/=8;
//                if(num_sensors%8 != 0){
//                    numPackets+=0x01;
//                }
//            }
//            if((numPackets) == temp){
//                readDataFunction();
//            }
//            num_sensors-=0x01;
//            data_index++;
        }
    }
    //Checks the TX buffer to see if the Master Module wants to read the data acquisition from the Pressure Module
    if(EUSCI_B1->IFG & BIT1){
        sendData();
        delay(2000);
        SYSCTL->REBOOT_CTL = 0x6901;        //Software Reset
    }
    EUSCI_B1->IFG = 0;                      //Clears the interrupt flag
}

/* Function loop is a default function for the Energia IDE, where as soon as the function setup execute, loop will execute afterwards
automatically. */
void loop() {
//  readDataFunction();
}
