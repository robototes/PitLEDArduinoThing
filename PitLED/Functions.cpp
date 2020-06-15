#include "Functions.h"

void show(CRGB* leds, int numLEDsPerStrand, int numStrands) {
  for (int i = 1; i < numStrands; i++) {
    for (int j = 0; j < numLEDsPerStrand; j++) {
      leds[numLEDsPerStrand * i + j] = leds[j];
    }
  }
  FastLED.show();
}

void printColor(CRGB color) {
  Serial.print("r: ");
  Serial.print(color.r);
  Serial.print(", g: ");
  Serial.print(color.g);
  Serial.print(", b: ");
  Serial.println(color.b);
}

void HSVFillFunction(CRGB* leds, int numLeds, int numStrands, CRGB color, int d, int repeats) {
  Serial.println("Starting HSVFill function");
  for (int i = 0; i < 255; i++) {
    CRGB color;
    hsv2rgb_rainbow(CHSV(i, 255, 255), color);
    for (int j = 0; j < numLeds; j++) {
      leds[j] = color;
    }
    show(leds, numLeds, numStrands);
    delay(d);
  }
  Serial.println("HSVFill function finished");
}

void HSVSwirlFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats) {
  Serial.println("Running HSVSwirl function");
  for (int i = 0; i < numLeds; i++) { // one rotation
    for (int k = 0 ; k < repeats; k++) {
      for (int j = 0; j < numLeds / repeats; j += 1) { //this loop jumps to the start of each new color segment by that length
        CRGB temp = CRGB(0, 0, 0);
        hsv2rgb_rainbow(CHSV((double)map(j, 0, numLeds / repeats, 0, 255), 255, 255), temp);
        leds[(i + j + k * numLeds / repeats) % numLeds] = temp;
      }
    }
    show(leds, numLeds, numStrands);
    delay(d);
  }
  Serial.println("HSVSwirl function completed");
}

void RainFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats) {
  Serial.println("Running Rain function");
  printColor(color);
  int center = 72;
  for (int dot = 0; dot < numLeds / 2; dot++)
  {
    leds[(center + dot) % numLeds] = color; // set this pixel to color
    if (center - dot < 0) {
      leds[(center - dot + numLeds) % numLeds] = color;
    } else {
      leds[(center - dot) % numLeds] = color;
    }

    show(leds, numLeds, numStrands);
    delay(d);
  }

  Serial.println("Rain function completed");
}

void RandomFadeFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats) {
  Serial.println("Running Random Fade function");
  printColor(color);

  int numAlready = 0;
  for (int i = 0; i < numLeds; i++) {
    if (leds[i] == color) {
      numAlready++;
    }
  }
  for (int dotRemaining = 0; dotRemaining < (numLeds - numAlready); dotRemaining++)
  {
    int randomSelection = random(numLeds);
    if (leds[randomSelection] == color) {
      dotRemaining --;
    } else {
      leds[randomSelection] = color; // set this pixel to color
      show(leds, numLeds, numStrands);
      delay(d);
    }
  }
  Serial.println("Random Fade function completed");
}

double lerp(int from, int to, double percent) {
  return from + (to - from) * percent;
}

CRGB lerp(CRGB from, CRGB to, double percent) {
  return CRGB(
           (int)lerp(from.red, to.red, percent),
           (int)lerp(from.green, to.green, percent),
           (int)lerp(from.blue, to.blue, percent)
         );
}

void SmoothFadeFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats) {
  Serial.println("Running Smooth Fade Function");
  printColor(color);
  CRGB oldLeds[numLeds];
  for (int i = 0; i < numLeds; i++) {
    oldLeds[i] = leds[i];
  }

  for (double i = 0; i < 1; i += 0.01) {
    for (int j = 0; j < numLeds; j++) {
      leds[j] = lerp(oldLeds[j], color, i);
    }
    show(leds, numLeds, numStrands);
    delay(d);
  }

  Serial.println("Smooth Fade Function completed");
}

void StartupFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int startDelay, int repeats) {
  Serial.println("Running Startup function");
  color = CRGB::Red;
  int d = startDelay;
  int dSub = (startDelay - repeats) / (5 * numStrands);
  for (int j = 0; j < numStrands; j++) {
    for (int i = 61; i < 83; i++) {
      leds[i + j * numLeds] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 12; i++) {
      leds[83 + i  + j * numLeds] = color;
      leds[62 - i + j * numLeds] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 24; i++) {
      leds[96 + i + j * numLeds] = color;
      leds[49 - i + j * numLeds] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 12; i++) {
      leds[121 + i + j * numLeds] = color;
      leds[22 - i + j * numLeds] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 134; i < 155; i++) {
      leds[i % numLeds + j * numLeds] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
  }
  Serial.println("Startup function completed");
}

void SweepFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats) {
  Serial.println("Running Sweep function");
  printColor(color);
  for (int dot = 0; dot < numLeds / repeats; dot++)
  {
    for (int i = 0; i < repeats; i++)
    {
      leds[(dot + i * numLeds / repeats) % numLeds] = color; // set this pixel to color, mod is to be safe
    }
    show(leds, numLeds, numStrands);
    delay(d);
  }
  Serial.println("Sweep function completed");
}

void SwirlFunction(CRGB* leds, int numLeds, int numStrands,  CRGB color, int d, int repeats) {
  Serial.println("Running swirl function");
  printColor(color);
  int numColors = (int)color.r % 2 + 2;
  CRGBPalette16 palette;
  if (numColors == 2) {
    palette = twoColors[color.g % TWOCOLORS];
  } else if (numColors == 3) {
    palette = threeColors[color.g % THREECOLORS];
  }
  int segmentLength = (int) floor(numLeds / (numColors * repeats));
  for (int startingLEDIndex = 0; startingLEDIndex < numLeds; startingLEDIndex++) { // The index of the LED where the first color segment starts.
    int colorIndex = 0; // The index of the current color we're using.
    int lastTransitionLEDIndex = startingLEDIndex; // The index of the LED in between the segments (where the strip changes color).
    for (int i = startingLEDIndex; i < startingLEDIndex + numLeds; i++) {
      int scaledIndex = i % numLeds; // Rescale so we loop back around to the beginning if startingLEDIndex is greater than zero.
      if (i - lastTransitionLEDIndex == segmentLength) { // New segment
        colorIndex = (colorIndex + 1) % numColors;
        lastTransitionLEDIndex = i;
      }
      leds[scaledIndex] = ColorFromPalette( palette, colorIndex * 16, 255, NOBLEND);
    }
    show(leds, numLeds, numStrands);
    delay(d);
  }
  Serial.println("Swirl function completed");
}
