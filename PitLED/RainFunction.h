#include <FastLED.h>
#include "LEDFunction.h"
#ifndef RAIN_H
#define RAIN_H

class RainFunction: public LEDFunction {
  public:
    RainFunction();
    void execute(CRGB * leds, int numLeds, int numStrands, CRGB color, int d);
    void show(CRGB * leds, int numLeds, int numStrands);
};

#endif
