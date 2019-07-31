#include <FastLED.h>
#include "LEDFunction.h"
#ifndef SWIRL_H
#define SWIRL_H

class SwirlFunction: public LEDFunction {
    int repeat;
  public:
    SwirlFunction(int repeats);
    void execute(CRGB* leds, int numLeds, int numStrands, CRGB colors[], int d);
    void show(CRGB* leds, int numLeds, int numStrands);
};

#endif
