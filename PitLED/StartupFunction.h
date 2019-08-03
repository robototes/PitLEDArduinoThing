#include <FastLED.h>
#include "LEDFunction.h"
#ifndef STARTUP_H
#define STARTUP_H

class StartupFunction: public LEDFunction {
    int dMin;
  public:
    StartupFunction(int _dMin);
    void execute(CRGB * leds, int numLeds, int numStrands, CRGB color, int d);
    void show(CRGB * leds, int numLeds, int numStrands);
};

#endif
