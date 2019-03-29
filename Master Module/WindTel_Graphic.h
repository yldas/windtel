/*
 * WindTel_Graphic.h
 *
 *  Created on: Mar 16, 2019
 *      Author: obed
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

void nextOption(Graphics_Context g_sContext, Graphics_Rectangle rect, int menuIndex,int currentOptionNum)
{
    rect.xMax = 315;
    rect.xMin = 8;
    rect.yMax = 80 + 25*(currentOptionNum-1);
    rect.yMin = 60 + 25*(currentOptionNum-1);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);
    if((menuIndex == 1 && currentOptionNum == 5) || (menuIndex == 4 && currentOptionNum == 3)){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 80;
        rect.yMin = 60;
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

    if(menuIndex == 1){
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setFont(&g_sContext, &g_sFontCmss20b);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
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

    if(menuIndex == 4){
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setFont(&g_sContext, &g_sFontCmss20b);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
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

}
void previousOption(Graphics_Context g_sContext, Graphics_Rectangle rect, int menuIndex,int currentOptionNum)
{
    rect.xMax = 315;
    rect.xMin = 8;
    rect.yMax = 80 + 25*(currentOptionNum-1);
    rect.yMin = 60 + 25*(currentOptionNum-1);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_drawRectangle(&g_sContext,&rect);
    Graphics_fillRectangle(&g_sContext,&rect);

    if(menuIndex == 1 && currentOptionNum == 1){
        rect.xMax = 315;
        rect.xMin = 8;
        rect.yMax = 180;
        rect.yMin = 160;
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

    if(menuIndex == 1){
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setFont(&g_sContext, &g_sFontCmss20b);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
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
    if(menuIndex == 4){
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setFont(&g_sContext, &g_sFontCmss20b);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
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

}
#endif /* WINDTEL_GRAPHIC_H_ */
