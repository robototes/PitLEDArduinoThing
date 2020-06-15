#include <FastLED.h>

#ifndef PitLED_H
#define PitLED_H

class PitLED {
    int numStrands, numLEDsPerStrand;
    CRGB* leds;
  public:
    PitLED(int strands, int ledsPerStrand);
    void init();
    void runFunction(void (*func)(CRGB*, int, int, CRGB, int, int), int d);
    void show();
    ~PitLED();
};

#endif
