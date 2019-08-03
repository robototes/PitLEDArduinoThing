#include "SwirlFunction.h"
#include "Arduino.h"
#include "PitLED.h"
#include <FastLED.h>

const TProgmemPalette16 FirstColors PROGMEM =
{
  CRGB::Red,
  CRGB::Blue,
  CRGB::White
};

const TProgmemPalette16 Seahawks PROGMEM =
{
  CRGB::Blue,
  CRGB::Green
};

const TProgmemPalette16 Huskies PROGMEM =
{
  CRGB::Yellow,
  CRGB::Purple
};

const TProgmemPalette16 Robototes PROGMEM =
{
  CRGB::Red,
  CRGB::Black,
};

const TProgmemPalette16 Sammamish PROGMEM =
{
  CRGB::Red,
  CRGB::Black,
  CRGB::White
};
#define TWOCOLORS 3
CRGBPalette16 twoColors[TWOCOLORS]  = {
  Robototes,
  Huskies,
  Seahawks
};
#define THREECOLORS 2
CRGBPalette16 threeColors[THREECOLORS]  = {
  FirstColors,
  Sammamish
};



SwirlFunction::SwirlFunction(int _repeats) {
  repeat = _repeats;
}
void SwirlFunction::execute(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d) {
  Serial.println("Running swirl function");
  int numColors = (int)random(2) + 2;
  CRGBPalette16 palette;
  if (numColors == 2) {
    palette = twoColors[random(TWOCOLORS)];
  }else if(numColors == 3){
    palette = threeColors[random(THREECOLORS)];
  }
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
      leds[scaledIndex] = ColorFromPalette( palette, colorIndex * 16, 255, NOBLEND);
    }
    show(leds, numLeds, numStrands);
    delay(d);
  }
  Serial.println("Swirl function completed");
}
void SwirlFunction::show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}
