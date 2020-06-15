#include <MemoryFree.h>
#include <FastLED.h>
#include "Functions.h"
#include "PitLED.h"

#define NUM_LEDS 144
#define DATA_PIN 5
#define NUM_STRANDS 6

void (* functions[])(CRGB*, int, int, CRGB, int, int) = {
  &SwirlFunction,
  &HSVFillFunction,
  &HSVSwirlFunction,
  &SweepFunction,
  &RandomFadeFunction,
  &RainFunction,
  &SmoothFadeFunction
};

PitLED pitLed(NUM_STRANDS, NUM_LEDS);
void setup()
{
  Serial.begin(9600);
  Serial.println("Starting program...");
  pitLed.runFunctionWithSet(&StartupFunction, 300, CRGB::Red, 60);
  randomSeed(0);
}

void loop()
{
  pitLed.runFunctionWithRandom(functions[random(7)], 20);
  Serial.print("Free Memory: ");
  Serial.println(freeMemory(), DEC);
  Serial.println();
}
