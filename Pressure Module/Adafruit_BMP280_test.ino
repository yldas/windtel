/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BMEP280 Breakout
  ----> http://www.adafruit.com/products/2651
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include "Adafruit_BMP280.h"
#include <msp.h>

#define BMP_SCK  (32)       //P3.5
#define BMP_MISO (31)       //P3.7
#define BMP_MOSI (11)       //P3.6
#define BMP_CS1  (75)       //P2.0
#define BMP_CS2  (76)       //P2.1
#define BMP_CS3  (77)       //P2.2
#define BMP_CS4  (34)       //P2.3
#define BMP_CS5  (38)       //P2.4
#define BMP_CS6  (19)       //P2.5
#define BMP_CS7  (39)       //P2.6
#define BMP_CS8  (40)       //P2.7
#define BMP_CS9  (24)       //P4.0
#define BMP_CS10 (5)        //P4.1
#define BMP_CS11 (12)       //P5.2
#define BMP_CS12 (6)        //P4.3
#define BMP_CS13 (26)       //P4.4
#define BMP_CS14 (27)       //P4.5
#define BMP_CS15 (8)        //P4.6
#define BMP_CS16 (28)       //P4.7

char data[32];          //pressure data of the sensors (each sensor have 2 bytes of data). The first index stores the number of sensors
int data_index = 0;     //index of data array
char num_sensors;       //num_sensors is the number of sensors used for the data acquisition
char numPackets;        //temporary variable that's used to denote the end of the reading in the I2C communication with master
int temp = 0;           //temp is a variable also used to denote the end of the reading of the communication protocol
float results_this[16]; //results array stores the results obtained from the sensors. Each sensor has two data: temperature and pressure respectively
float results_next[32];
float results_psi[16];
float results_psi_frac[16];

//Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
Adafruit_BMP280 bmp1(BMP_CS1, BMP_MOSI, BMP_MISO,  BMP_SCK);
Adafruit_BMP280 bmp2(BMP_CS2, BMP_MOSI, BMP_MISO,  BMP_SCK);
Adafruit_BMP280 bmp3(BMP_CS3, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp4(BMP_CS4, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp5(BMP_CS5, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp6(BMP_CS6, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp7(BMP_CS7, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp8(BMP_CS8, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp9(BMP_CS9, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp10(BMP_CS10, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp11(BMP_CS11, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp12(BMP_CS12, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp13(BMP_CS13, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp14(BMP_CS14, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp15(BMP_CS15, BMP_MOSI, BMP_MISO,  BMP_SCK);
//Adafruit_BMP280 bmp16(BMP_CS16, BMP_MOSI, BMP_MISO,  BMP_SCK);

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  __enable_irq();
  NVIC->ISER[0] = 1 << (EUSCIB0_IRQn);
  NVIC->ISER[0] = 1 << (EUSCIB1_IRQn);
}

void setSampling(Adafruit_BMP280 bmp){
    /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X1,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X4,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

float convertToF(float celsius){
  return celsius*1.8 + 32.0;
}

//  if (!bmp.begin()) {
//    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
//    while(1);
//  }

//Initiates the I2C communication with the Master Module through ports 6.4 (SDA) and 6.5 (SCL)
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

//Initiates an I2C communication with a Pressure Module Slave through ports 1.6 (SDA) and 1.7 (SCL)
void init2(){
    EUSCI_B0->CTLW0 = BIT0;                         //UCSWRST = 1b = software reset enabled
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_MST;           //Selects this micro-controller as master
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_MODE_3;        //I2C mode
    EUSCI_B0->CTLW0 |= BIT6;                        //UCSSEL0 = 01b = clk src set to ACLK
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR;            //Sets bus to transmit
    EUSCI_B0->BRW = (uint16_t) 0x20;                //Baud rate set to 0x20 ~ 4 kilo bits per second
    P1SEL0 |= BIT6;
    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT7;
    P1SEL1 &= ~BIT7;
    EUSCI_B0->CTLW0 &= ~BIT0;                       //UCSWRST = 1b = software reset disabled
}

//Converts the integer parameter num to a string a sends it to the Master Module
void convertToChars(int num, int digits){
    int temp1 = num;
    int multiple = 1;
    int i = 0;
    int count = 0;
    if(num == 0){
        for(; i < digits; i++){
            while(!(EUSCI_B1->IFG & BIT1));
            EUSCI_B1->TXBUF = '0';
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
                while(!(EUSCI_B1->IFG & BIT1));
                EUSCI_B1->TXBUF = '0';
            }else{
                multiple/= 10;
                digit = temp1/multiple;
                if(digit == 0){
                    while(!(EUSCI_B1->IFG & BIT1));
                    EUSCI_B1->TXBUF = '0';
                }else{
                    while(!(EUSCI_B1->IFG & BIT1));
                    EUSCI_B1->TXBUF = digit+'0';
                }
                temp1 %= multiple;
            }
            j++;
        }
    }
}

//This function will transmit the result stored on the array results as a string of characters to its Master
void sendData(void){
    int i;
    int temp1 = 0;
    for(i = 0; i < 4; i++){
        temp1 = i*2 + 1;
        convertToChars(results[temp1], 6);
    }
    i = 0;
    temp1 = 0;
    int integer = 0;
    float fraction1 = 0.0;
    int fraction = 0;
    float value = 0.0;
    for(; i < 4; i++){
        temp1 = i*2 + 1;
        integer = results[temp1]/6894.76;
        value = results[temp1]/6894.76;
        fraction1 = (value - integer)*100.0;
        fraction = fraction1;
        results_psi_frac[i] = fraction;
        results_psi[i] = integer;
        convertToChars(results_psi[i], 2);
        while(!(EUSCI_B1->IFG & BIT1));
        EUSCI_B1->TXBUF = '@';
        convertToChars(results_psi_frac[i], 2);
    }
    EUSCI_B1->CTLW0 |= BIT2;                //STOP
    delay(320000);
}

//This function will initialize the SPI communication with the pressure sensors, configure each sensor, as well as obtain their data and send
//it to the Master Module
void readDataFunction(){
  delay(1000);
  bmp1.begin();
  setSampling(bmp1);
  Serial.println("Sensor 1:");
  Serial.print(F("Temperature = "));
  results[0] = convertToF(bmp1.readTemperature());
  Serial.print(results[0]);
  Serial.println(" *F");
  Serial.print(F("Pressure = "));
  results[1] = bmp1.readPressure();
  Serial.print(results[1]);
  Serial.println(" Pa");
  Serial.println();
  
  delay(1000);
  bmp2.begin();
  setSampling(bmp2);
  Serial.println("Sensor 2:");
  Serial.print(F("Temperature = "));
  Serial.print(convertToF(bmp2.readTemperature()));
  Serial.println(" *F");
  Serial.print(F("Pressure = "));
  Serial.print(bmp2.readPressure());
  Serial.println(" Pa");
  Serial.println();
  
  delay(1000);
  bmp3.begin();
  setSampling(bmp3);
  Serial.println("Sensor 3:");
  Serial.print(F("Temperature = "));
  Serial.print(convertToF(bmp3.readTemperature()));
  Serial.println(" *F");
  Serial.print(F("Pressure = "));
  Serial.print(bmp3.readPressure());
  Serial.println(" Pa");
  Serial.println();

//  delay(1000);
//  bmp4.begin();
//  setSampling(bmp4);
//  Serial.println("Sensor 4:");
//  Serial.print(F("Temperature = "));
//  Serial.print(convertToF(bmp4.readTemperature()));
//  Serial.println(" *F");
//  Serial.print(F("Pressure = "));
//  Serial.print(bmp4.readPressure());
//  Serial.println(" Pa");
//  Serial.println();

//  delay(1000);
//  bmp6.begin();
//  setSampling(bmp6);
//  Serial.println("Sensor 6:");
//  Serial.print(F("Temperature = "));
//  Serial.print(convertToF(bmp6.readTemperature()));
//  Serial.println(" *F");
//  Serial.print(F("Pressure = "));
//  Serial.print(bmp6.readPressure());
//  Serial.println(" Pa");
//  Serial.println();

//  delay(1000);
//  if (!bmp16.begin()) {
//    Serial.println(F("Could not find a valid BMP280 sensor 16, check wiring!"));
//    while(1);
//  }
//  setSampling(bmp16);
//  Serial.println("Sensor 16:");
//  Serial.print(F("Temperature = "));
//  Serial.print(convertToF(bmp16.readTemperature()));
//  Serial.println(" *F");
//  Serial.print(F("Pressure = "));
//  Serial.print(bmp16.readPressure());
//  Serial.println(" Pa");
//  Serial.println();
//  delay(1000);
}

//I2C interrupt handler. The Pressure Module will read the command from the Master Module, and the Pressure Module will proceed to execute
//the instructed command.
void EUSCIB1_IRQHandler(void){
    //Checks the RX buffer to see if the Master Module has sent a command
    if(EUSCI_B1->IFG & BIT0){
//        temp++;
        while(!(EUSCI_B1->IFG & BIT0));     //Rx flag
        char x = EUSCI_B1->RXBUF;
        if(x == 0xFF){
            SYSCTL->REBOOT_CTL = 0x6901;    //Software Reset
        }else if(x == 0x55){
          char y = EUSCI_B1->RXBUF;
          int i =0;
          for(i; i < y; i++){
            results_next[i] = EUSCI_B1->RXBUF;
          }
        }
        else{
            num_sensors = x;
//            if(data_index == 0){
////                num_sensors = data[0];
////                numPackets = num_sensors;
////                numPackets/=8;
//                if(num_sensors%8 != 0){
//                    numPackets+=0x01;
//                }
//            }
            if((numPackets) == temp){
                readDataFunction();
            }
            num_sensors-=0x01;
            data_index++;
        }
    }
    //Checks the TX buffer to see if the Master Module wants to read the data acquisition from the Pressure Module
    if(EUSCI_B1->IFG & BIT1){
        sendData();
//        SYSCTL->REBOOT_CTL = 0x6901;        //Software Reset
    }
    EUSCI_B1->IFG = 0;                      //Clears the interrupt flag
}

void loop() {
//  readDataFunction();
}
