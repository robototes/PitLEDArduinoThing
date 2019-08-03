#include <FastLED.h>
#include "LEDFunction.h"
#ifndef RANDOMFADE_H
#define RANDOMFADE_H

class RandomFadeFunction: public LEDFunction {
  public:
    RandomFadeFunction();
    void execute(CRGB * leds, int numLeds, int numStrands, CRGB color, int d);
    void show(CRGB * leds, int numLeds, int numStrands);
};

#endif
