#include "FastLED.h"
#define NUM_LEDS 300 
CRGB leds[NUM_LEDS];
#define PIN 5 

void setup()
{
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}

// *** REPLACE FROM HERE ***
void loop() {
  RunningLights(0xff,0,0);        // red
  RunningLights(0xff,0xff,0xff);  // white
  RunningLights(0,0,0xff);        // blue
}

void RunningLights(byte red, byte green, byte blue) {
  int Position=0;
  int colorChange = 0;
  
  for(int j=0; j<NUM_LEDS; j++)
  {
    colorChange++;
    if(colorChange >= 3) {
      colorChange = 0;
    }
    
    for(int k = 0; k <= 1; k++) {

      if(colorChange == 0){
        red = 0xff;
        green = 0;
        blue = 0;
      } else if( colorChange == 1) {
        red = 0xff;
        green = 0xff;
        blue = 0xff;
      } else {
        red = 0;
        green = 0;
        blue = 0xff;
      }
        
      
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {


        colorChange++;
        if(colorChange >= 16) {
          colorChange = 0;
        }

    
        if(colorChange == 5){
          red = 0xff;
          green = 0;
          blue = 0;
        } else if(colorChange == 10) {
          red = 0xff;
          green = 0xff;
          blue = 0xff;
        } else if(colorChange == 15) {
          red = 0;
          green = 0;
          blue = 0xff;
        }
      
        // sine wave, 3 offset waves make a rainbow!
//        float level = sin(i+Position) * 127 + 128;
//        setPixel(i,level,0,0);
//        float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }

    }
      
      showStrip();
  }
}
// *** REPLACE TO HERE ***

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
