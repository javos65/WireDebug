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
uint32_t i,x = 0xDEAFBEAF;

WDebug("Loading"); 
for( i = 0; i<10;++i) { WDebug("."); delay(100);}   // loading with point-trail
WDebug("\b\b\b\b\b\b Ready !"); delay(2000);

WDebug("\nLoading  ");        
for( i = 0; i<30;++i) { 
  if (i%4==0) {WDebug("\b\\");delay(150);}   // loading with star rotating
  if (i%4==1) {WDebug("\b-"); delay(150);}   
  if (i%4==2) {WDebug("\b/"); delay(150);}   
  if (i%4==3) {WDebug("\b|"); delay(150);}   
  }
WDebug("\b  Ready !"); delay(2000);    

WDebug("\nLoading   ");        
for( i = 0; i<30;++i) { 
  if (i%3==0) {WDebug("\b\b >"); delay(100);}   // loading with star rotating
  if (i%3==1) {WDebug("\b\b< "); delay(100);}   
  if (i%3==2) {WDebug("\b\b  "); delay(100);}   
   
  }
WDebug("\b\b  Ready !");   
}

void loop() {
}



