#include <FastLED.h>
#ifndef HSVFILLFUNC_H
#define HSVFILLFUNC_H

class HSVFillFunction: public LEDFunction {
  public:
    HSVFillFunction();
    virtual void execute(CRGB* leds, int numLeds, int numStrands, CRGB color, int d);
    void show(CRGB* leds, int numLeds, int numStrands);
};

#endif
