#include <FastLED.h>
#include "Functions.h"
#include "PitLED.h"



#define NUM_LEDS 144
#define DATA_PIN 5
#define NUM_STRANDS 15

PitLED pitLed(NUM_STRANDS, NUM_LEDS);
void setup()
{
  Serial.begin(9600);
  Serial.println("Starting program...");
  pitLed.runFunction(&StartupFunction, 300);
  randomSeed(0);
}

void loop()
{
  void (* functions [5])(CRGB*, int, int, CRGB, int, int);

  functions[0] = &SwirlFunction;
//  functions[1] = &HSVFillFunction;
//  functions[2] = &HSVSwirlFunction;
  functions[1] = &SweepFunction;
  functions[2] = &RandomFadeFunction;
  functions[3] = &RainFunction;
  functions[4] = &SmoothFadeFunction;

  pitLed.runFunction(functions[random(5)], 20);
}
