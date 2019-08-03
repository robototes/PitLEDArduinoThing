#include "HSVSwirlFunction.h"
#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>




HSVSwirlFunction::HSVSwirlFunction(int _repeats) {
  repeat = _repeats;
}
void HSVSwirlFunction::execute(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d) {
  Serial.println("Running HSVSwirl function");
  for (int i = 0; i < numLeds; i++) { // one rotation
    for (int k = 0 ; k < repeat; k++) {
      for (int j = 0; j < numLeds/ repeat; j += 1) { //this loop jumps to the start of each new color segment by that length
        CRGB temp = CRGB(0, 0, 0);
        hsv2rgb_rainbow(CHSV((double)map(j, 0, numLeds / repeat, 0, 255), 255, 255), temp);
        leds[(i + j + k * numLeds / repeat) % numLeds] = temp;
      }
    }
    show(leds, numLeds, numStrands);
    FastLED.delay(d);
  }
  Serial.println("HSVSwirl function completed");
}
void HSVSwirlFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
