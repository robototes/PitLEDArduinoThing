#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 5
#define NUM_STRANDS 15

CRGB leds[NUM_LEDS * NUM_STRANDS];

CRGB CONSTCOLORS[8] = {
  CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Orange, CRGB::Cyan, CRGB::Purple, CRGB::White
};


CRGB GOODCOLORS[6][3] = {
  {CRGB::Green, CRGB::Blue, NULL}, {CRGB::Red, CRGB::Black, NULL}, {CRGB::Red, CRGB::White, CRGB::Black }, {CRGB::White, CRGB::Black, NULL}, {CRGB::Purple, CRGB::Yellow, NULL}, {CRGB::Red, CRGB::White, CRGB::Blue}
};

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS * NUM_STRANDS);
  randomSeed(analogRead(0));
  startup(CRGB::Red, 300, 60);
}

void show() {
  for (int i = 1; i < NUM_STRANDS; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[NUM_LEDS * i + j] = leds[j];
    }
  }
  FastLED.show();
}




void loop()
{
  pickRandomFunction();
}

void fillAll(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  show();
}

void pickRandomFunction() {
  int randomPick = random(0, 7);
  //  int randomPick = 2; // 2 is stuck, 3 works, 4 crashes after a while (turns black), 5 and 6 work
  if (randomPick == 0) {
    HSVFill(30);
  }


  else if (randomPick == 1) {
    HSVSwirl(30, (int)random(1, 3));
  }



  else if (randomPick == 2) {
    CRGB colors[3] = GOODCOLORS[random(sizeof(GOODCOLORS) / sizeof(GOODCOLORS[0]))];
    if (colors[2]) {
      newSwirl(colors, 3, 1, random(2, 6));
    } else {
      newSwirl(colors, 2, 1, random(2, 6));
    }
  }



  else if (randomPick == 3) {
    CRGB color = CONSTCOLORS[random(sizeof(CONSTCOLORS))];
    sweep(color.red, color.green, color.blue, 30, random(0, 5), 0);
  }


  else if (randomPick == 4) {
    CRGB color = CONSTCOLORS[random(sizeof(CONSTCOLORS))];
    randomFade(color.red, color.green, color.blue, 30);
  }


  else if (randomPick == 5) {
    CRGB color = CONSTCOLORS[random(sizeof(CONSTCOLORS))];
    rain(color.red, color.green, color.blue, 30, 0);
  }

  else if (randomPick == 6) {
    CRGB color = CONSTCOLORS[random(sizeof(CONSTCOLORS))];
    smoothFade(color, 30);
  }
}


void HSVFill(int d) {
  for (int i = 0; i < 360; i++) {
    CRGB color;
    hsv2rgb_spectrum(CHSV(i, 255, 255 / 2), color);
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = color;
    }
    show();
    delay(d);
  }
}


void HSVSwirl(int d, int repeat) { // colors to display, delay between movement, number of times each color shows up. try to make colors * repeat  = 144.
  for (int i = 0; i < NUM_LEDS; i++) { // one rotation
    for (int k = 0 ; k < repeat; k++) {
      for (int j = 0; j < NUM_LEDS / repeat; j += 1) { //this loop jumps to the start of each new color segment by that length
        CRGB temp = CRGB(0, 0, 0);
        hsv2rgb_spectrum(CHSV((double)map(j, 0, NUM_LEDS / repeat, 0, 255), 255, 255), temp);
        leds[(i + j + k * NUM_LEDS / repeat) % NUM_LEDS] = temp;
      }
    }
    show();
    delay(d);
  }
}



void swirl( CRGB colors[], int numColors,  int d, int repeat) { // colors to display, delay between movement, number of times each color shows up. try to make colors * repeat  = 144.


  for (int i = 0; i < NUM_LEDS; i++) { // one rotation
    int currentColor = 0;
    for (int j = 0; j < NUM_LEDS; j += NUM_LEDS / (numColors * repeat)) { //this loop jumps to the start of each new color segment by that length
      for (int k = 0; k < NUM_LEDS / (numColors * repeat) ; k++) { // display each led with correct color
        leds[(i + j + k) % NUM_LEDS] = colors[currentColor % numColors];
      }
      currentColor++;
    }
    show();
    delay(d);
  }
}

void newSwirl(CRGB colors[], int numColors,  int d, int repeat) {
  int segmentLength = (int) floor(NUM_LEDS / (numColors * repeat));
  for (int startingLEDIndex = 0; startingLEDIndex < NUM_LEDS; startingLEDIndex++) { // The index of the LED where the first color segment starts.
    int colorIndex = 0; // The index of the current color we're using.
    int lastTransitionLEDIndex = startingLEDIndex; // The index of the LED in between the segments (where the strip changes color).
    for (int i = startingLEDIndex; i < startingLEDIndex + NUM_LEDS; i++) {
      int scaledIndex = i % NUM_LEDS; // Rescale so we loop back around to the beginning if startingLEDIndex is greater than zero.
      if (i - lastTransitionLEDIndex == segmentLength) { // New segment
        colorIndex = (colorIndex + 1) % numColors;
        lastTransitionLEDIndex = i;
      }
      leds[scaledIndex] = colors[colorIndex];
    }
    show();
    delay(d);
  }
}

void sweep(byte red, byte green, byte blue, int d, int times, int startPoint)
{
  for (int dot = 0; dot < NUM_LEDS / times; dot++)
  {
    for (int i = 0; i < times; i++)
    {
      leds[(dot + i * NUM_LEDS / times + startPoint) % NUM_LEDS] = CRGB( red, green, blue); // set this pixel to color, mod is to be safe
    }
    show();
    delay(d);
  }
}

void randomFade(byte red, byte green, byte blue, int d)
{
  CRGB newColor = CRGB(red, green, blue);
  for (int dotRemaining = 0; dotRemaining < NUM_LEDS; dotRemaining++)
  {
    int randomSelection = random(NUM_LEDS);
    if (leds[randomSelection] == newColor) {
      dotRemaining --;
    } else {
      leds[randomSelection] = CRGB( red, green, blue); // set this pixel to color
      show();
      delay(d);
    }
  }
}

void rain(byte red, byte green, byte blue, int d, int center)
{
  for (int dot = 0; dot < NUM_LEDS / 2; dot++)
  {
    leds[(center + dot) % NUM_LEDS] = CRGB( red, green, blue); // set this pixel to color
    if (center - dot < 0) {
      leds[(center - dot + NUM_LEDS) % NUM_LEDS] = CRGB(red, green, blue);
    } else {
      leds[(center - dot) % NUM_LEDS] = CRGB(red, green, blue);
    }

    show();
    delay(d);
  }
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

void smoothFade(CRGB toColor, int d) {
  CRGB oldLeds[NUM_LEDS];
  for (int i = 0; i < NUM_LEDS; i++) {
    oldLeds[i] = leds[i];
  }

  for (double i = 0; i < 1; i += 0.01) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = lerp(oldLeds[j], toColor, i);
    }
    delay(d);
    show();
  }
}



void startup(CRGB color, int startDelay, int minDelay) {
  int d = startDelay;
  int dSub = (startDelay - minDelay) / (5 * NUM_STRANDS);
  fillAll(CRGB::Black);
  for (int j = 0; j < NUM_STRANDS; j++) {
    for (int i = 61; i < 83; i++) {
      leds[i + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 12; i++) {
      leds[83 + i  + j * 144] = color;
      leds[62 - i + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 24; i++) {
      leds[96 + i + j * 144] = color;
      leds[49 - i + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 0; i < 12; i++) {
      leds[121 + i + j * 144] = color;
      leds[22 - i + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
    for (int i = 134; i < 155; i++) {
      leds[i % 144 + j * 144] = color;
    }
    FastLED.show();
    delay(d);
    d -= dSub;
  }
}
