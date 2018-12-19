#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
  CRGB swirlColors[2] = {CRGB(0, 0, 0), CRGB(0, 0, 255)};

  swirl(swirlColors, 30, 6);

}


void swirl( CRGB colors[], int d, int repeat) { // colors to display, delay between movement, number of times each color shows up. try to make colors * repeat  = 144.
  int len = sizeof(colors);
  for (int i = 0; i < NUM_LEDS; i++) { // one rotation
    int currentColor = 0;
    for (int j = 0; j < NUM_LEDS; j += NUM_LEDS / (len * repeat)) { //this loop jumps to the start of each new color segment by that length
      for (int k = 0; k < NUM_LEDS / (len * repeat) ; k++) { // display each led with correct color
        leds[(i + j + k) % NUM_LEDS] = colors[currentColor%len];
      }
      currentColor++;
    }
    FastLED.show();
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
