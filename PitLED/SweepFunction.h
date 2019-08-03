#include <FastLED.h>
#include "LEDFunction.h"
#ifndef SWEEP_H
#define SWEEP_H

class SweepFunction: public LEDFunction {
    int repeat;
  public:
    SweepFunction(int _repeats);
    void execute(CRGB * leds, int numLeds, int numStrands, CRGB color, int d);
    void show(CRGB * leds, int numLeds, int numStrands);
};

#endif
