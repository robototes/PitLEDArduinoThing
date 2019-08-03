#include "RandomFadeFunction.h"
#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>




RandomFadeFunction::RandomFadeFunction() {
}
void RandomFadeFunction::execute(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d) {
  Serial.println("Running Random Fade function");

  int numAlready = 0;
  for (int i = 0; i < numLeds; i++) {
    if (leds[i] == color) {
      numAlready++;
    }
  }
  for (int dotRemaining = 0; dotRemaining < (numLeds - numAlready); dotRemaining++)
  {
    int randomSelection = random(numLeds);
    if (leds[randomSelection] == color) {
      dotRemaining --;
    } else {
      leds[randomSelection] = color; // set this pixel to color
      show(leds, numLeds, numStrands);
      FastLED.delay(d);
    }
  }
  Serial.println("Random Fade function completed");
}
void RandomFadeFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
