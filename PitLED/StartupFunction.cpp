#include "StartupFunction.h"
#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>

StartupFunction::StartupFunction(int _dMin) {
  dMin = _dMin;
}
void StartupFunction::execute(CRGB* leds, int numLeds, int numStrands,  CRGB color, int startDelay) {
  Serial.println("Running Startup function");
  color = CRGB::Red;
  int d = startDelay;
  int dSub = (startDelay - dMin) / (5 * numStrands);
  for (int j = 0; j < numStrands; j++) {
    for (int i = 61; i < 83; i++) {
      leds[i + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 12; i++) {
      leds[83 + i  + j * 144] = color;
      leds[62 - i + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 24; i++) {
      leds[96 + i + j * 144] = color;
      leds[49 - i + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 12; i++) {
      leds[121 + i + j * 144] = color;
      leds[22 - i + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 134; i < 155; i++) {
      leds[i % 144 + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
  }
  Serial.println("Startup function completed");
}
void StartupFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
