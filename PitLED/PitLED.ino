#include <MemoryFree.h>
#include <pgmStrToRAM.h>

//#include <PitLED.h>

#include <FastLED.h>
#include "PitLED.h"
#include "SwirlFunction.h"
#include "HSVFillFunction.h"
#include "HSVSwirlFunction.h"
#include "SweepFunction.h"
#include "RandomFadeFunction.h"
#include "RainFunction.h"
#include "SmoothFadeFunction.h"
#include "StartupFunction.h"
#include "LEDFunction.h"
#define NUM_LEDS 144
#define DATA_PIN 5
#define NUM_STRANDS 15

CRGB leds[NUM_LEDS * NUM_STRANDS];
PitLED pitLed(NUM_STRANDS, NUM_LEDS);
void setup()
{
  Serial.begin(9600);
  Serial.println("Starting program...");
  StartupFunction * startupFunction = new StartupFunction(60);
  pitLed.runFunction( startupFunction, 300);
  randomSeed(analogRead(0));
}

void loop()
{

  LEDFunction* functions[7];

  functions[0] = new SwirlFunction(random(6) + 1);
  functions[1] = new HSVFillFunction();
  functions[2] = new HSVSwirlFunction(random(6) + 1);
  functions[3] = new SweepFunction(random(6) + 1);
  functions[4] = new RandomFadeFunction();
  functions[5] = new RainFunction();
  functions[6] = new SmoothFadeFunction();

  pitLed.runFunction(functions[random(7)], 20);
  Serial.print("Free Memory: ");
  Serial.println(freeMemory(), DEC);
  Serial.println();
}
