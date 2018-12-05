#include <FastLED.h>
    #define NUM_LEDS 144
    #define DATA_PIN 6

CRGB leds[NUM_LEDS];

void setup()
{
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
//  sweep(255,0,0,30);
//  sweep(0,0,0,30);
//  sweep(0,255,0,30);
//  sweep(0,0,0,30);
//  sweep(0,0,255,30);
//  sweep(0,0,0,30);
//  sweep(255,255,255,30);
//  sweep(0,0,0,30);

  CRGB swirlColors[2]= {CRGB(0,0,0), CRGB(0,0,255)};

  swirl(swirlColors,30, 6);
  
}


void swirl( CRGB colors[], int d, int repeat){

//  for(int j = 0; j < 144; j++){ //do one complete rotation
//    for(int i = 0; i< NUM_LEDS; i +=NUM_LEDS/sizeof(colors)){ // go through each color stepping a certain amount
//
//      for(int l = 0; l < sizeof(colors); l++){ // go through each color again...
//        for(int k = 0; k < NUM_LEDS/sizeof(colors); k++){ // and for some reason again
//          leds[(i+j+k+l*sizeof(colors))%144 ] = colors[l]; // MaTH yAy!
//        }
//      }  
//    }
//    FastLED.show();
//    delay(d);
//  }

  int len = sizeof(colors);
  for(int i = 0; i < NUM_LEDS; i++){ // one rotation
    for(int j = 0; j < NUM_LEDS; j+= NUM_LEDS/(len*repeat)){ // len = sizeof(colors) this loop jumps to the start of each new color with the repeat amount
      for(int k = 0; k < NUM_LEDS/(len*repeat) ; k++){ // display each led with correct color
          leds[(i+j+k)%NUM_LEDS] = colors[NUM_LEDS/j];
      }
    }
    FastLED.show();
    delay(d);
  } 
}



void sweep(byte red, byte green, byte blue, int d)
{
    for(int dot = 0; dot < NUM_LEDS; dot++)
    { 
        leds[dot] = CRGB( red, green, blue); // set this pixel to color
        FastLED.show();
        //leds[dot] = CRGB::Black;  // clear this led for the next time around the loop
        delay(d);
    }
}
/*

//Example 1: set color from red, green, and blue components individually
  // The three color channel values can be referred to as "red", "green", and "blue"...
    leds[i].red   = 50;
    leds[i].green = 100;
    leds[i].blue  = 150;
  
  // ...or, using the shorter synonyms "r", "g", and "b"...
    leds[i].r = 50;
    leds[i].g = 100;
    leds[i].b = 150;
  
  // ...or as members of a three-element array:
    leds[i][0] = 50;  // red
    leds[i][1] = 100; // green
    leds[i][2] = 150; // blue

//Example 2: set color from red, green, and blue components all at once
  leds[i] = CRGB( 50, 100, 150);
  
// Example 3: set color via 'hex color code' (0xRRGGBB)
  leds[i] = 0xFF007F;

// Example 4: set color via any named HTML web color
  leds[i] = CRGB::HotPink;

// Example 5: set color via setRGB
  leds[i].setRGB( 50, 100, 150);

*/
