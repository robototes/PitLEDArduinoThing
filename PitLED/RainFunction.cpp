#include "RainFunction.h"
#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>




RainFunction::RainFunction() {
}
void RainFunction::execute(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d) {
  Serial.println("Running Rain function");
  int center = 72;
  for (int dot = 0; dot < numLeds / 2; dot++)
  {
    leds[(center + dot) % numLeds] = color; // set this pixel to color
    if (center - dot < 0) {
      leds[(center - dot + numLeds) % numLeds] = color;
    } else {
      leds[(center - dot) % numLeds] = color;
    }

    show(leds, numLeds, numStrands);
    FastLED.delay(d);
  }

  Serial.println("Rain function completed");
}
void RainFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
