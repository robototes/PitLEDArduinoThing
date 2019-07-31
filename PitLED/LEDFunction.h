#include <FastLED.h>
#ifndef LEDFUNC_H
#define LEDFUNC_H

class LEDFunction {
  public:
    virtual void execute(CRGB* leds, int numLeds,int numStrands, CRGB colors[], int d);
    void show(CRGB* leds, int numLeds,int numStrands);
};

#endif
