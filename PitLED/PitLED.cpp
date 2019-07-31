#include <FastLED.h>

#include "PitLED.h"
#include "LEDFunction.h"


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

void PitLED::runFunction(LEDFunction *function, int d) {
  CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Orange};
  function->execute(leds, numLEDsPerStrand, numStrands, colors, d);
}
