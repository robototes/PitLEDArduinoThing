#include <FastLED.h>
#include "Arduino.h"
#include "PitLED.h"
#include "RobototesColors.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void show(CRGB* leds, int numLEDsPerStrand, int numStrands);

void HSVFillFunction(CRGB* leds, int numLeds, int numStrands, CRGB color, int d, int repeats);

void HSVSwirlFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats);

void RainFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats);

void RandomFadeFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats);

double lerp(int from, int to, double percent);

CRGB lerp(CRGB from, CRGB to, double percent);

void SmoothFadeFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats);

void StartupFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int startDelay, int repeats);

void SweepFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats);

void SwirlFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats);

#endif
