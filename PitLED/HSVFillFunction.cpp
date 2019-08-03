#include "Arduino.h"
#include "PitLED.h"
#include "HSVFillFunction.h"
#include <FastLED.h>

HSVFillFunction::HSVFillFunction(){
  
}

void HSVFillFunction::execute(CRGB* leds, int numLeds, int numStrands, CRGB color, int d) {
  Serial.println("Starting HSVFill function");
  for (int i = 0; i < 255; i++) {
    CRGB color;
    hsv2rgb_rainbow(CHSV(i, 255, 255), color);
    for (int j = 0; j < numLeds; j++) {
      leds[j] = color;
    }
    show(leds, numLeds, numStrands);
    FastLED.delay(d);
  }
  Serial.println("HSVFill function finished");
}

void HSVFillFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
