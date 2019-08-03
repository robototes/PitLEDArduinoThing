#include "SmoothFadeFunction.h"
#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>

double lerp(int from, int to, double percent) {
  return from + (to - from) * percent;
}

CRGB lerp(CRGB from, CRGB to, double percent) {
  return CRGB(
           (int)lerp(from.red, to.red, percent),
           (int)lerp(from.green, to.green, percent),
           (int)lerp(from.blue, to.blue, percent)
         );
}


SmoothFadeFunction::SmoothFadeFunction() {
}
void SmoothFadeFunction::execute(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d) {
  Serial.println("Running Smooth Fade Function");
  
  CRGB oldLeds[numLeds];
  for (int i = 0; i <numLeds; i++) {
    oldLeds[i] = leds[i];
  }

  for (double i = 0; i < 1; i += 0.01) {
    for (int j = 0; j < numLeds; j++) {
      leds[j] = lerp(oldLeds[j], color, i);
    }
    show(leds, numLeds, numStrands);
    FastLED.delay(d);
  }

  Serial.println("Smooth Fade Function completed");
}
void SmoothFadeFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
