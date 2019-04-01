/*
 * WindTel_Graphic.h
 *
 *  Created on: Mar 16, 2019
 *      Author: Luis O. Vega Maisonet
 */
/* Standard Includes */
#include <stdint.h>
#include "DriverLibFiles/driverlib.h"
/* GrLib Includes */
#include "DriverLibFiles/grlib.h"
#include "DriverLibFiles/button.h"
#include "DriverLibFiles/imageButton.h"
#include "DriverLibFiles/radioButton.h"
#include "DriverLibFiles/checkbox.h"
#include "LcdDriver/kitronix320x240x16_ssd2119_spi.h"
#include "images/images.h"
#include "DriverLibFiles/touch_P401R.h"

#ifndef WINDTEL_GRAPHIC_H_
#define WINDTEL_GRAPHIC_H_
int count = 0;
int time = 1000;
char windTunnelVelocity[5];
char rod_LengthBalance[6] = {'0','c','m',' '};


//Delay function takes 16 bit number (in milliseconds) and performs a delay
void Delay(uint32_t msec){
    uint32_t i = 0;
    //Converts the milliseconds to seconds and uses the system's clock speed for the delay
    uint32_t time = (msec / 1000) * (SYSTEM_CLOCK_SPEED / 15);

    //Empty loop for the delay
    for(i = 0; i < time; i++)
    {
        ;
    }
}

//Converts an integer number to an array of characters, also known as a string
void tostring(char str[], int num){
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

//Initialization procedure of the display
void boardInit(){
    FPU_enableModule();
}

//Initializes the clock of the display
void clockInit(void){
    /* 2 flash wait states, VCORE = 1, running off DC-DC, 48 MHz */
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setPowerState(PCM_AM_DCDC_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    CS_setDCOFrequency(48000000);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, 1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, 1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, 1);
}

void drawMainMenu(Graphics_Context g_sContext, Graphics_Rectangle rect){
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_clearDisplay(&g_sContext);
    rect.xMax = 315;
    rect.xMin = 8;
    rect.yMax = 80;
    rect.yMin = 60;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext,"Wind Tunnel Telemetry System", AUTO_STRING_LENGTH, 8,10,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Main Menu", AUTO_STRING_LENGTH, 8,35,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"1. System Reset", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"2. Object Weight Elimination", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"3. Perform Experiment", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"4. Speed Control", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"5. Diagnostics", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
}

void drawSpeedControlMenu(Graphics_Context g_sContext, Graphics_Rectangle rect){
    P2->OUT &= ~BIT0;
    Delay(1000);
    P2->OUT &= ~BIT1;
    Delay(1000);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_clearDisplay(&g_sContext);
    rect.xMax = 315;
    rect.xMin = 8;
    rect.yMax = 80;
    rect.yMin = 60;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext,"Wind Tunnel Telemetry System", AUTO_STRING_LENGTH, 8,10,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Speed Control Menu", AUTO_STRING_LENGTH, 8,35,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"1. Increase Speed", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"2. Decrease Speed", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"3. Return to Main Menu", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Current Wind Speed:", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
}

void updateWindSpeed(Graphics_Context g_sContext,char *cSpeed){
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext,cSpeed, AUTO_STRING_LENGTH, 212,160,GRAPHICS_TRANSPARENT_TEXT);

}

void drawPerformExperimentMenu(Graphics_Context g_sContext, Graphics_Rectangle rect){
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_clearDisplay(&g_sContext);
    rect.xMax = 315;
    rect.xMin = 8;
    rect.yMax = 105;
    rect.yMin = 85;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext,"Wind Tunnel Telemetry System", AUTO_STRING_LENGTH, 8,10,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Perform Experiment Menu", AUTO_STRING_LENGTH, 8,35,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"1.Enter the rod length:", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,rod_LengthBalance, AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"2.Confirm the selected length", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"3.Return to Main Menu", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
}

void updateRodLength(Graphics_Context g_sContext,int rod_Length,Graphics_Rectangle rect){
    tostring(rod_LengthBalance,rod_Length);
    if(rod_Length<10){
        rod_LengthBalance[1] = 'c';
        rod_LengthBalance[2] = 'm';
        rod_LengthBalance[3] = ' ';

    }
    else if(rod_Length<100){
        rod_LengthBalance[2] = 'c';
        rod_LengthBalance[3] = 'm';
        rod_LengthBalance[4] = ' ';

    }
    else{
        rod_LengthBalance[3] = 'c';
        rod_LengthBalance[4] = 'm';
        rod_LengthBalance[5] = ' ';

    }
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    rect.xMax = 315;
    rect.xMin = 8;
    rect.yMax = 105;
    rect.yMin = 85;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    if(rod_Length)
        Graphics_drawString(&g_sContext,rod_LengthBalance, AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);
    else
        Graphics_drawString(&g_sContext,"0cm", AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);

}

void drawParameterMenu(Graphics_Context g_sContext, Graphics_Rectangle rect){
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_clearDisplay(&g_sContext);
    rect.xMax = 315;
    rect.xMin = 8;
    rect.yMax = 80;
    rect.yMin = 60;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext,"Wind Tunnel Telemetry System", AUTO_STRING_LENGTH, 8,10,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Select parameters to measure", AUTO_STRING_LENGTH, 8,35,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"1.Barometric Pressure", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"2.Wind Exerted Forces", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"3.Relative Humidity", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"4.Temperature", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"5.Return to Main Menu", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
}

void drawPressureMenu(Graphics_Context g_sContext, Graphics_Rectangle rect){
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_clearDisplay(&g_sContext);
    rect.xMax = 112;
    rect.xMin = 8;
    rect.yMax = 80;
    rect.yMin = 60;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext,"Wind Tunnel Telemetry System", AUTO_STRING_LENGTH, 8,10,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Select pressure sensors", AUTO_STRING_LENGTH, 8,35,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  1 [ ]", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  2 [ ]", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  3 [ ]", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  4 [ ]", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  5 [ ]", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  6 [ ]", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  7 [ ]", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  8 [ ]", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);

}

void drawMorePressureMenu(Graphics_Context g_sContext, Graphics_Rectangle rect){
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_clearDisplay(&g_sContext);
    rect.xMax = 112;
    rect.xMin = 8;
    rect.yMax = 80;
    rect.yMin = 60;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext,"Wind Tunnel Telemetry System", AUTO_STRING_LENGTH, 8,10,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Select pressure sensors", AUTO_STRING_LENGTH, 8,35,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor  9 [ ]", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor 10 [ ]", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor 11 [ ]", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor 12 [ ]", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor 13 [ ]", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor 14 [ ]", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor 15 [ ]", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Sensor 16 [ ]", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
    Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
}
void selectSensor(Graphics_Context g_sContext, Graphics_Rectangle rect,int currentOptionNum){
    int cursorPosition = 87 + (currentOptionNum-2)*25;
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_LIGHT_GREEN);
    if(currentOptionNum == 1)
        Graphics_drawString(&g_sContext,"X", AUTO_STRING_LENGTH, 126,62,GRAPHICS_TRANSPARENT_TEXT);
    else if(currentOptionNum < 6)
        Graphics_drawString(&g_sContext,"X", AUTO_STRING_LENGTH, 112,cursorPosition,GRAPHICS_TRANSPARENT_TEXT);
    else{
        cursorPosition = 87 + (currentOptionNum-6)*25;
        Graphics_drawString(&g_sContext,"X", AUTO_STRING_LENGTH, 254,cursorPosition,GRAPHICS_TRANSPARENT_TEXT);
    }
}

void nextSensor(Graphics_Context g_sContext, Graphics_Rectangle rect,int menuIndex, char selectedSensors[48],int currentOptionNum){
    if(currentOptionNum == 1){
        rect.xMax = 112;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-1);
        rect.yMin = 60 + 25*(currentOptionNum-1);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 130;
        rect.xMin = 8;
        rect.yMax = 80 + 25*currentOptionNum;
        rect.yMin = 60 + 25*currentOptionNum;

    }
    if(currentOptionNum < 5){
        rect.xMax = 100;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-1);
        rect.yMin = 60 + 25*(currentOptionNum-1);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 100;
        rect.xMin = 8;
        rect.yMax = 80 + 25*currentOptionNum;
        rect.yMin = 60 + 25*currentOptionNum;

    }
    else if(currentOptionNum == 5){
        rect.xMax = 100;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-1);
        rect.yMin = 60 + 25*(currentOptionNum-1);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 243;
        rect.xMin = 150;
        rect.yMax = 105 + 25*(currentOptionNum-5);
        rect.yMin = 85 + 25*(currentOptionNum-5);
    }
    else if((currentOptionNum > 5) && (currentOptionNum <= 8)){
        rect.xMax = 243;
        rect.xMin = 150;
        rect.yMax = 105 + 25*(currentOptionNum-6);
        rect.yMin = 85 + 25*(currentOptionNum-6);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 243;
        rect.xMin = 150;
        rect.yMax = 105 + 25*(currentOptionNum-5);
        rect.yMin = 85 + 25*(currentOptionNum-5);
    }
    else if(currentOptionNum == 9){
        rect.xMax = 243;
        rect.xMin = 150;
        rect.yMax = 80 + 25*(currentOptionNum-5);
        rect.yMin = 60 + 25*(currentOptionNum-5);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-4);
        rect.yMin = 60 + 25*(currentOptionNum-4);
    }
    else if(currentOptionNum == 10){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-5);
        rect.yMin = 60 + 25*(currentOptionNum-5);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-4);
        rect.yMin = 60 + 25*(currentOptionNum-4);
    }
    else if(currentOptionNum == 11){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-5);
        rect.yMin = 60 + 25*(currentOptionNum-5);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 112;
        rect.xMin = 8;
        rect.yMax = 80;
        rect.yMin = 60;

    }

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

    if(menuIndex == 7){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  1", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"Sensor  1", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  2", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"Sensor  2", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  3", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 4){
            Graphics_drawString(&g_sContext,"Sensor  3", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  4", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 5){
            Graphics_drawString(&g_sContext,"Sensor  4", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  5", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 6){
            Graphics_drawString(&g_sContext,"Sensor  5", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  6", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 7){
            Graphics_drawString(&g_sContext,"Sensor  6", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  7", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 8){
            Graphics_drawString(&g_sContext,"Sensor  7", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  8", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 9){
            Graphics_drawString(&g_sContext,"Sensor  8", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 10){
            Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 11){
            Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
        }
    }
    if(menuIndex == 8){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  9", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"Sensor  9", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 10", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"Sensor 10", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 11", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 4){
            Graphics_drawString(&g_sContext,"Sensor 11", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 12", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 5){
            Graphics_drawString(&g_sContext,"Sensor 12", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 13", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 6){
            Graphics_drawString(&g_sContext,"Sensor 13", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 14", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 7){
            Graphics_drawString(&g_sContext,"Sensor 14", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 15", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 8){
            Graphics_drawString(&g_sContext,"Sensor 15", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 16", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 9){
            Graphics_drawString(&g_sContext,"Sensor 16", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 10){
            Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 11){
            Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
        }
    }
}

void previousSensor(Graphics_Context g_sContext, Graphics_Rectangle rect,int menuIndex, char selectedSensors[48],int currentOptionNum){

    if(currentOptionNum == 1){
        rect.xMax = 112;
        rect.xMin = 8;
        rect.yMax = 80;
        rect.yMin = 60;

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 230;
        rect.yMin = 210;
    }
    else if(currentOptionNum == 2){
        rect.xMax = 112;
        rect.xMin = 8;
        rect.yMax = 105;
        rect.yMin = 85;

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 112;
        rect.xMin = 8;
        rect.yMax = 80;
        rect.yMin = 60;
    }
    else if(currentOptionNum < 6){
        rect.xMax = 100;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-1);
        rect.yMin = 60 + 25*(currentOptionNum-1);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 100;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-2);
        rect.yMin = 60 + 25*(currentOptionNum-2);

    }
    else if(currentOptionNum == 6){
        rect.xMax = 243;
        rect.xMin = 150;
        rect.yMax = 105 + 25*(currentOptionNum-6);
        rect.yMin = 85 + 25*(currentOptionNum-6);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 100;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-2);
        rect.yMin = 60 + 25*(currentOptionNum-2);

    }
    else if((currentOptionNum > 5) && (currentOptionNum <= 9)){
        rect.xMax = 243;
        rect.xMin = 150;
        rect.yMax = 105 + 25*(currentOptionNum-6);
        rect.yMin = 85 + 25*(currentOptionNum-6);

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 243;
        rect.xMin = 150;
        rect.yMax = 105 + 25*(currentOptionNum-7);
        rect.yMin = 85 + 25*(currentOptionNum-7);

    }
    else if(currentOptionNum == 10){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 205;
        rect.yMin = 185;

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);

        rect.xMax = 243;
        rect.xMin = 150;
        rect.yMax = 180;
        rect.yMin = 160;
    }
    else if(currentOptionNum == 11){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 230;
        rect.yMin = 210;

        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawRectangle(&g_sContext,&rect);
        Graphics_fillRectangle(&g_sContext,&rect);
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 205;
        rect.yMin = 185;
    }

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

    if(menuIndex == 7){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  1", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"Sensor  1", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  2", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 4){
            Graphics_drawString(&g_sContext,"Sensor  2", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  3", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 5){
            Graphics_drawString(&g_sContext,"Sensor  3", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  4", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 6){
            Graphics_drawString(&g_sContext,"Sensor  4", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  5", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 7){
            Graphics_drawString(&g_sContext,"Sensor  5", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  6", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 8){
            Graphics_drawString(&g_sContext,"Sensor  6", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  7", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 9){
            Graphics_drawString(&g_sContext,"Sensor  7", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  8", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 10){
            Graphics_drawString(&g_sContext,"Sensor  8", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 11){
            Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
        }
    }

    if(menuIndex == 8){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"All Sensors [ ]", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor  9", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"Sensor  9", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 10", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 4){
            Graphics_drawString(&g_sContext,"Sensor 10", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 11", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 5){
            Graphics_drawString(&g_sContext,"Sensor 11", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 12", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 6){
            Graphics_drawString(&g_sContext,"Sensor 12", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 13", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 7){
            Graphics_drawString(&g_sContext,"Sensor 13", AUTO_STRING_LENGTH, 150,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 14", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 8){
            Graphics_drawString(&g_sContext,"Sensor 14", AUTO_STRING_LENGTH, 150,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 15", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 9){
            Graphics_drawString(&g_sContext,"Sensor 15", AUTO_STRING_LENGTH, 150,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Sensor 16", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 10){
            Graphics_drawString(&g_sContext,"Sensor 16", AUTO_STRING_LENGTH, 150,160,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 11){
            Graphics_drawString(&g_sContext,"More Sensors", AUTO_STRING_LENGTH, 8,185,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"Return to Parameter Menu", AUTO_STRING_LENGTH, 8,210,GRAPHICS_TRANSPARENT_TEXT);
        }
    }
}
void nextOption(Graphics_Context g_sContext, Graphics_Rectangle rect, int menuIndex,int currentOptionNum,int rod_Length)
{
    rect.xMax = 315;
    rect.xMin = 8;

    if(menuIndex != 3){
        rect.yMax = 80 + 25*(currentOptionNum-1);
        rect.yMin = 60 + 25*(currentOptionNum-1);
    }
    else{
        rect.yMax = 105 + 25*(currentOptionNum-1);
        rect.yMin = 85 + 25*(currentOptionNum-1);
    }
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    if((menuIndex == 1 && currentOptionNum == 5) || (menuIndex == 4 && currentOptionNum == 3) || (menuIndex == 6 && currentOptionNum == 5)){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 80;
        rect.yMin = 60;
    }
    else if(menuIndex == 3){
        if(currentOptionNum == 3){
            rect.xMax = 315;
            rect.xMin = 8;
            rect.yMax = 105;
            rect.yMin = 85;
        }
        else
        {
            rect.xMax = 315;
            rect.xMin = 8;
            rect.yMax = 105 + 25*currentOptionNum;
            rect.yMin = 85 + 25*currentOptionNum;
        }
    }
    else{
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 80 + 25*currentOptionNum;
        rect.yMin = 60 + 25*currentOptionNum;
    }

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

    if(menuIndex == 1){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"1. System Reset", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"2. Object Weight Elimination", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"2. Object Weight Elimination", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3. Perform Experiment", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"3. Perform Experiment", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"4. Speed Control", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 4){
            Graphics_drawString(&g_sContext,"4. Speed Control", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"5. Diagnostics", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 5){
            Graphics_drawString(&g_sContext,"1. System Reset", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"5. Diagnostics", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
    }

    if(menuIndex == 3){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"1.Enter the rod length:", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            if(rod_Length)
                Graphics_drawString(&g_sContext,rod_LengthBalance, AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);
            else
                Graphics_drawString(&g_sContext,"0cm", AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);

            Graphics_drawString(&g_sContext,"2.Confirm the selected length", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"2.Confirm the selected length", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3.Return to Main Menu", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"1.Enter the rod length:", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            if(rod_Length)
                Graphics_drawString(&g_sContext,rod_LengthBalance, AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);
            else
                Graphics_drawString(&g_sContext,"0cm", AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3.Return to Main Menu", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
    }
    if(menuIndex == 4){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"1. Increase Speed", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"2. Decrease Speed", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"2. Decrease Speed", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3. Return to Main Menu", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"1. Increase Speed", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3. Return to Main Menu", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
    }

    if(menuIndex == 6){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"1.Barometric Pressure", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"2.Wind Exerted Forces", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"2.Wind Exerted Forces", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3.Relative Humidity", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"3.Relative Humidity", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"4.Temperature", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 4){
            Graphics_drawString(&g_sContext,"4.Temperature", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"5.Return to Main Menu", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 5){
            Graphics_drawString(&g_sContext,"1.Barometric Pressure", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"5.Return to Main Menu", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
    }

}
void previousOption(Graphics_Context g_sContext, Graphics_Rectangle rect, int menuIndex,int currentOptionNum,int rod_Length)
{
    rect.xMax = 315;
    rect.xMin = 8;
    if(menuIndex !=3){
        rect.yMax = 80 + 25*(currentOptionNum-1);
        rect.yMin = 60 + 25*(currentOptionNum-1);
    }
    else{
        rect.yMax = 105 + 25*(currentOptionNum-1);
        rect.yMin = 85 + 25*(currentOptionNum-1);
    }
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);

    if((menuIndex == 1 && currentOptionNum == 1) || (menuIndex == 6 && currentOptionNum == 1)){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 180;
        rect.yMin = 160;
    }
    else if(menuIndex == 3){
        if(currentOptionNum == 1){
            rect.xMax = 315;
            rect.xMin = 8;
            rect.yMax = 155;
            rect.yMin = 135;
        }
        else
        {
            rect.xMax = 315;
            rect.xMin = 8;
            rect.yMax = 105 + 25*(currentOptionNum-2);
            rect.yMin = 85 + 25*(currentOptionNum-2);
        }
    }
    else if(menuIndex == 4 && currentOptionNum == 1){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 130;
        rect.yMin = 110;
    }
    else{
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 80 + 25*(currentOptionNum-2);
        rect.yMin = 60 + 25*(currentOptionNum-2);
    }
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    if(menuIndex == 1){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"1. System Reset", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"5. Diagnostics", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"1. System Reset", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"2. Object Weight Elimination", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"2. Object Weight Elimination", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3. Perform Experiment", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 4){
            Graphics_drawString(&g_sContext,"3. Perform Experiment", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"4. Speed Control", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 5){
            Graphics_drawString(&g_sContext,"4. Speed Control", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"5. Diagnostics", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
    }
    if(menuIndex == 3){
        if(currentOptionNum == 1){
            if(rod_Length)
                Graphics_drawString(&g_sContext,rod_LengthBalance, AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);
            else
                Graphics_drawString(&g_sContext,"0cm", AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3.Return to Main Menu", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            if(rod_Length)
                Graphics_drawString(&g_sContext,rod_LengthBalance, AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);
            else
                Graphics_drawString(&g_sContext,"0cm", AUTO_STRING_LENGTH,115,85,GRAPHICS_TRANSPARENT_TEXT);

            Graphics_drawString(&g_sContext,"2.Confirm the selected length", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"2.Confirm the selected length", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3.Return to Main Menu", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
    }
    if(menuIndex == 4){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"1. Increase Speed", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3. Return to Main Menu", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"1. Increase Speed", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"2. Decrease Speed", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"2. Decrease Speed", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3. Return to Main Menu", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
    }

    if(menuIndex == 6){
        if(currentOptionNum == 1){
            Graphics_drawString(&g_sContext,"1.Barometric Pressure", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"5.Return to Main Menu", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 2){
            Graphics_drawString(&g_sContext,"1.Barometric Pressure", AUTO_STRING_LENGTH, 8,60,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"2.Wind Exerted Forces", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 3){
            Graphics_drawString(&g_sContext,"2.Wind Exerted Forces", AUTO_STRING_LENGTH, 8,85,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"3.Relative Humidity", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 4){
            Graphics_drawString(&g_sContext,"3.Relative Humidity", AUTO_STRING_LENGTH, 8,110,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"4.Temperature", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
        }
        else if(currentOptionNum == 5){
            Graphics_drawString(&g_sContext,"4.Temperature", AUTO_STRING_LENGTH, 8,135,GRAPHICS_TRANSPARENT_TEXT);
            Graphics_drawString(&g_sContext,"5.Return to Main Menu", AUTO_STRING_LENGTH, 8,160,GRAPHICS_TRANSPARENT_TEXT);
        }
    }

}
#endif /* WINDTEL_GRAPHIC_H_ */
