/*****************************************************************************
* | File      	:	WireDebug.h
* | Function    :	debug with Serial print to external I2C Display
* | Info        : JV 2024
*----------------
* |	This version:   V1.0
* | Date        :   2024-01-16
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __WDEBUG_H
#define __WDEBUG_H

#include "stdio.h"

// display specifications : I2C Oled
#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 32        // OLED display height, in pixels
#define OLED_RESET     -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C     // < See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define MAXLINECHARS 20
#define MAXLINES 4
#define CHARW 6
#define CHARH 8
// define derives I2C port
#define MYWIRE Wire2 //define your serial out -> Wire2 is Portenta HAT connector I2C2


// Global required variables and functions
extern char G_Textbuffer[80];
extern uint8_t InitWDebug();
extern uint8_t Text2Oled(char *B);
extern void SetWraptext(uint8_t w);

// Define Inline Function
#define WDEBUG 1
#if WDEBUG
	#define WDebug(__info,...) sprintf(G_Textbuffer,__info,##__VA_ARGS__);Text2Oled(G_Textbuffer);
#else
	#define WDebug(__info,...)  
#endif


#endif
