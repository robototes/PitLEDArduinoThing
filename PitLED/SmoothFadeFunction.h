#include <FastLED.h>
#include "LEDFunction.h"
#ifndef SMOOTH_H
#define SMOOTH_H

class SmoothFadeFunction: public LEDFunction {
  public:
    SmoothFadeFunction();
    void execute(CRGB * leds, int numLeds, int numStrands, CRGB color, int d);
    void show(CRGB * leds, int numLeds, int numStrands);
};

#endif
