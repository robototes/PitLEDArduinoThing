#include "SweepFunction.h"
#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>




SweepFunction::SweepFunction(int _repeats) {
  repeat = _repeats;
}
void SweepFunction::execute(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d) {
  Serial.println("Running Sweep function");
  for (int dot = 0; dot < numLeds / repeat; dot++)
  {
    for (int i = 0; i < repeat; i++)
    {
      leds[(dot + i * numLeds / repeat) % numLeds] = color; // set this pixel to color, mod is to be safe
    }
    show(leds, numLeds, numStrands);
    FastLED.delay(d);
  }
  Serial.println("Sweep function completed");
}
void SweepFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
