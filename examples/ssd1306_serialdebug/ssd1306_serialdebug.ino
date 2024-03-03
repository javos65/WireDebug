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
InitWDebug();SetWraptext(0); // init I2C oled, set text wrapping off

WDebug("Testing 1.2.3.");
WDebug("4.5.6.7.\n"); // appends text, + new line
WDebug("012345678901234567890123456789\n"); // text non-wrapped + new line
WDebug("Next Line\n");
WDebug("Another Line ... ");delay(2000);
WDebug("Last Line");;delay(2000);           // appends on line 4
WDebug("\nNew Line, scroll up");            // scrolls up
}

void loop() {
}



