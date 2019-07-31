#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>

void LEDFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}

void LEDFunction::execute(CRGB* leds, int numLeds, int numStrands, CRGB colors[], int d) {
  Serial.println("Running base red function");
  for (int i = 0; i < numLeds; i++) {
    leds[i] = CRGB::Red;
  }
  show(leds, numLeds, numStrands);
  delay(1000);
}
