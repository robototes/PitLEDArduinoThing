#include <FastLED.h>
#include "LEDFunction.h"
#ifndef HSVSWIRL_H
#define HSVSWIRL_H

class HSVSwirlFunction: public LEDFunction {
    int repeat;
  public:
    HSVSwirlFunction(int _repeats);
    void execute(CRGB * leds, int numLeds, int numStrands, CRGB color, int d);
    void show(CRGB * leds, int numLeds, int numStrands);
};

#endif
