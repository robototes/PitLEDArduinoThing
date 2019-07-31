#include <FastLED.h>
#include "LEDFunction.h"

#ifndef PitLED_H
#define PitLED_H

class PitLED {
    int numStrands, numLEDsPerStrand;
    CRGB* leds;
  public:
    PitLED(int strands, int ledsPerStrand);
    void init();
    void runFunction(LEDFunction *function, int d);
    void show();
    ~PitLED();
};

#endif
