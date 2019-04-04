#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 5

#define NUM_STRANDS 15

CRGB leds[NUM_LEDS * NUM_STRANDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS * NUM_STRANDS);
}

void loop() {
  for(int i = 0; i < NUM_LEDS * NUM_STRANDS; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  delay(100);
}
