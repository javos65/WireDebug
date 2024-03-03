/**************************************************************************
 This is an example for Adafruit Monochrome OLEDs based on SSD1306 drivers

 This example is for a 128x32 pixel display using I2C to communicate.
 Defining a Debug-print function to Oled display

 2024 -JV
 Adapt you WireDebug.h for your display : current version uses SSD1306
 **************************************************************************/
 
#include "WireDebug.h"

void setup() {
Serial.begin(9600);delay(2000);
InitWDebug();SetWraptext(1); // init I2C oled, set text wrapping off

float analog = 0.00234;
uint32_t x = 0xDEAFBEAF;

WDebug("Testing 1.2.3.");delay(2000);
WDebug("4.5.6.7.8\n"); delay(2000);// appends text, + new line
WDebug("Value = %f\n",analog); // text non-wrapped + new line
WDebug("Next Line\n");delay(2000);
WDebug("Hex %04X ",x);delay(2000);
WDebug("append Line\n");;delay(2000);        // appends on line 4
WDebug("New Line, scroll up");            // scrolls up
}

void loop() {
}



