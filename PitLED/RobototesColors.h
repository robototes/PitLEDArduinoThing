#include <FastLED.h>

#ifndef COLORS_H
#define COLORS_H

#define NUMCOLORS 4
CRGB CONSTCOLORS[NUMCOLORS] = {
  CRGB::Red, CRGB::Blue, CRGB::White, CRGB::Black
};

const TProgmemPalette16 FirstColors PROGMEM =
{
  CRGB::Red,
  CRGB::Blue,
  CRGB::White
};

const TProgmemPalette16 Seahawks PROGMEM =
{
  CRGB::Blue,
  CRGB::Green
};

const TProgmemPalette16 Huskies PROGMEM =
{
  CRGB::Yellow,
  CRGB::Purple
};

const TProgmemPalette16 Robototes PROGMEM =
{
  CRGB::Red,
  CRGB::Black,
};

const TProgmemPalette16 Sammamish PROGMEM =
{
  CRGB::Red,
  CRGB::Black,
  CRGB::White
};
#define TWOCOLORS 1
CRGBPalette16 twoColors[TWOCOLORS]  = {
  Robototes
//  Huskies,
//  Seahawks
};

#define THREECOLORS 2
CRGBPalette16 threeColors[THREECOLORS]  = {
  FirstColors,
  Sammamish
};

#endif
