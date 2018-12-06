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
  sweep(255,0,0,30,4);
}

void sweep(byte red, byte green, byte blue, int d, int times, int startPoint)
{
  for (int dot = 0; dot < NUM_LEDS/times; dot++)
  {
    for(int i = 0; i< times; i++)
    {
      leds[(dot+i*NUM_LEDS/times + startPoint)%NUM_LEDS] = CRGB( red, green, blue); // set this pixel to color, mod is to be safe
    }
    FastLED.show();
    delay(d);
  }
}
