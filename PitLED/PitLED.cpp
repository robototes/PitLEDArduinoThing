#include <FastLED.h>

#include "PitLED.h"
#include "RobototesColors.h"


PitLED::PitLED(int strands, int ledsPerStrand) {
  numStrands = strands;
  numLEDsPerStrand = ledsPerStrand;
  init();
}

void PitLED::init() {
  leds = new CRGB[numLEDsPerStrand * numStrands];
  FastLED.addLeds<NEOPIXEL, 5>(leds, (int) numLEDsPerStrand * numStrands);
  for (int i = 0; i < numLEDsPerStrand * numStrands; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(1000);
  for (int i = 0; i < numLEDsPerStrand * numStrands; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  delay(1000);
  for (int i = 0; i < numLEDsPerStrand * numStrands; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(1000);
}

PitLED::~PitLED() {
  delete leds;
}

void PitLED::runFunctionWithRandom(void (*func)(CRGB*, int, int, CRGB, int, int), int d) {
  CRGB color = CONSTCOLORS[random(NUMCOLORS)];
  runFunctionWithSet(func, d, color, random(5) + 1);
}

void PitLED::runFunctionWithSet(void (*func)(CRGB*, int, int, CRGB, int, int), int d, CRGB color, int repeats) {
  func(leds, numLEDsPerStrand, numStrands, color, d, repeats);
}
