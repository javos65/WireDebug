
#include "WireDebug.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

char G_Textbuffer[80];
uint8_t G_Linepointer=0,G_Charpointer=0,G_Wraptext=0;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &MYWIRE, OLED_RESET);


//shift up display content vertcial wih <l>, fill new sapce with <f> bit pattern
void Scrollup(uint8_t l, uint8_t f)
{
 uint8_t XW,YW,b;
 uint8_t *p = display.getBuffer(); // get display buffer pointer
 if (l>( (SCREEN_HEIGHT/CHARH) -1) ) l= (SCREEN_HEIGHT/CHARH)-1;
 XW = SCREEN_WIDTH/8; // write bytes = 8 pixels
 YW = SCREEN_HEIGHT-(CHARH*l);

 // move display up l lines,  => 128x32 display this is 16 bytes per line, 3x8 = 24 lines
 for(int y = 0; y<YW; y++ )
  for(int x=0;x<XW;x++) { *(p+x + y*XW) = *(p+x + (y+CHARH)*XW );  }

 // fill remaining lines with f
 for(int y = YW; y<SCREEN_HEIGHT; ++y )
  for(int x=0;x<XW;++x) {*(p+x + y*XW) = f; }
 display.display(); 
}

//erase character at Text cursor
void Erasecharacter()
{
int16_t starty = G_Linepointer *CHARH ;
int16_t startx = G_Charpointer*CHARW;
display.setCursor(startx,starty);
for(int y = 0; y<CHARH; y++)
  for(int x=0; x<CHARW; x++ ) display.drawPixel(startx+x,starty+y,SSD1306_BLACK);
 display.display();   
}

void SetWraptext(uint8_t w)
 {
  G_Wraptext=w;
  }

// intialise the Display for debug messages
uint8_t InitWDebug()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // set to 3.3V source
    printf("SSD1306 allocation failed\n"); 
    return 0;
    }
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0,0);               // Start at top-left corner
  display.display();                    // send buffer to display
  return 1;
}

// Write text to Oled like a character display. no character wrapping, if line has more than 20 characters, no print
// if /n (carriage return) is received, new line. If display is full, scrolls up one line
uint8_t Text2Oled(char *B)
{
    int i,t=0;
    char c;
    display.setCursor(G_Charpointer*CHARW,G_Linepointer*CHARH);
    for(i=0;i<64;++i)  // print max 64 characters
        {
        c = B[i];
        if ( c==0 ){break;} // stop at end of string of end of display
        if (c == '\n'){ // end of line
            G_Linepointer++ ; if (G_Linepointer == MAXLINES) {G_Linepointer = MAXLINES-1; Scrollup(1, 0x00);}
            G_Charpointer = 0;
            display.setCursor(G_Charpointer*CHARW,G_Linepointer*CHARH);
            }
        else 
          if (c>=32 ) { // && G_Charpointer<MAXLINECHARS
            if ( (G_Charpointer<MAXLINECHARS) ) {
                display.write(c); t++;// write valid ascii character
                G_Charpointer++;
                }
            else if (G_Wraptext)    { // end of the line, and wrapping text is on : make new line, print character
                G_Linepointer++ ; if (G_Linepointer == MAXLINES) {G_Linepointer = MAXLINES-1; Scrollup(1, 0x00);}
                G_Charpointer = 0;
                display.setCursor(G_Charpointer*CHARW,G_Linepointer*CHARH);
                display.write(c); t++;  // write valid ascii character
                G_Charpointer++;
                }
            }
            else if(c=='\b') {  // handle non printable character backspace
                if (G_Charpointer==0) {G_Charpointer = SCREEN_WIDTH/CHARW-1;G_Linepointer--;}
                 else G_Charpointer--;
                Erasecharacter();
                }
        }   
    display.display();
    //Serial.print("printed #characters :");Serial.println(t);
    return t;
}
