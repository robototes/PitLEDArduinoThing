#include "SwirlFunction.h"
#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>

SwirlFunction::SwirlFunction(int _repeats) {
  repeat = _repeats;
}
void SwirlFunction::execute(CRGB* leds, int numLeds, int numStrands,  CRGB colors[], int d) {
  Serial.println("Running swirl function");
  int numColors = 3;
  Serial.println(sizeof(colors));
  Serial.println(sizeof(colors[0]));
  Serial.println(sizeof(colors[1]));
  Serial.println(sizeof(colors[2]));
  int segmentLength = (int) floor(numLeds / (numColors * repeat));
  for (int startingLEDIndex = 0; startingLEDIndex < numLeds; startingLEDIndex++) { // The index of the LED where the first color segment starts.
    int colorIndex = 0; // The index of the current color we're using.
    int lastTransitionLEDIndex = startingLEDIndex; // The index of the LED in between the segments (where the strip changes color).
    for (int i = startingLEDIndex; i < startingLEDIndex + numLeds; i++) {
      int scaledIndex = i % numLeds; // Rescale so we loop back around to the beginning if startingLEDIndex is greater than zero.
      if (i - lastTransitionLEDIndex == segmentLength) { // New segment
        colorIndex = (colorIndex + 1) % numColors;
        lastTransitionLEDIndex = i;
      }
      leds[scaledIndex] = colors[colorIndex];
    }
    show(leds, numLeds, numStrands);
    delay(d);
  }
  Serial.println("Swirl function completed");
}
void SwirlFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  Serial.println(numStrands);
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
