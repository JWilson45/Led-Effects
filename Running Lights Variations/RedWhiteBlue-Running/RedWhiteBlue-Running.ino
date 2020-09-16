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
  RunningLights();
}

void RunningLights() {
  byte red;
  byte green;
  byte blue;
  int Position=0;
  int colorChange = 0;
  
  for(int j=0; j<NUM_LEDS * 10; j++)
  {
    colorChange++;
    if(colorChange >= 3) {
      colorChange = 0;
    }   
      
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {


        // Change the color of the lights every 6th light
        colorChange++;
        // Reset counter at 16 back to 0
        if(colorChange >= 16) {
          colorChange = 0;
        }


        // Set color RED
        if(colorChange == 5){
          red = 0xff;
          green = 0;
          blue = 0;

        // Set color WHITE
        } else if(colorChange == 10) {
          red = 0xff;
          green = 0xff;
          blue = 0xff;

        // Set color BLUE
        } else if(colorChange == 15) {
          red = 0;
          green = 0;
          blue = 0xff;
        }

        // Sin wave
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);

     }
      
      showStrip();
  }
}
// *** REPLACE TO HERE ***

void showStrip() {
   // FastLED
   FastLED.show();
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
