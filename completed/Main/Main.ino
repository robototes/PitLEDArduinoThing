#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 5

#define NUM_STRANDS 6

CRGB leds[NUM_LEDS * NUM_STRANDS];
//CRGB allLeds[NUM_LEDS * NUM_STRANDS];

//CRGB BLUE = CRGB(0, 0, 255);
//CRGB GREEN  = CRGB(0, 255, 0);
//CRGB RED = CRGB(255, 0, 0);
//CRGB YELLOW = CRGB(255 / 2, 255 / 2, 0);
//CRGB ORANGE = CRGB(255, 40, 0);
//CRGB CYAN = CRGB(0, 255, 200);
//CRGB PURPLE = CRGB(255 / 2, 0, 255 / 3);
//CRGB BLACK = CRGB(0, 0, 0);
//CRGB WHITE = CRGB(255, 255, 255);

CRGB CONSTCOLORS[8] = {
  CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Orange, CRGB::Cyan, CRGB::Purple, CRGB::White
};


CRGB GOODCOLORS[6][3] = {
  {CRGB::Green, CRGB::Blue, NULL}, {CRGB::Red, CRGB::Black, NULL}, {CRGB::Red, CRGB::White, NULL}, {CRGB::White, CRGB::Black, NULL}, {CRGB::Purple, CRGB::Yellow, NULL}, {CRGB::Red, CRGB::White, CRGB::Blue}
};




void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS * NUM_STRANDS);
  //Serial.begin(9600);
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
//  Serial.println(millis());
  pickRandomFunction();
//  Serial.println(millis());
//  fillAll(CRGB::Blue);
//  delay(1000);
//  fillAll(CRGB::Green);
//  delay(1000);
}

void fillAll(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  show();
}

void pickRandomFunction() {
  int randomPick = random(0, 7);
  //randomPick = 4;

  if (randomPick == 0) {
    HSVFill(30);
  }


  else if (randomPick == 1) {
    HSVSwirl(30, (int)random(1, 3));
  }



  else if (randomPick == 2) {
    CRGB colors[3] = GOODCOLORS[random(sizeof(GOODCOLORS))];
    if (colors[2]) {
      swirl(colors, 3, 30, random(0, 6));
    } else {
      swirl(colors, 2, 30, random(0, 6));
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
        //leds[(i + j + k * NUM_LEDS / repeat) % NUM_LEDS] = calculateRGB((double)map(j, 0, NUM_LEDS / repeat, 0, 360));
        //leds[(i + j + k * NUM_LEDS / repeat) % NUM_LEDS] = hueColors[(int)map(j, 0, NUM_LEDS / repeat, 0, hueRes)];
        hsv2rgb_spectrum(CHSV(360 / (NUM_LEDS / repeat), 255, 255 / 2), leds[(i + j + k * NUM_LEDS / repeat) % NUM_LEDS]);

      }
    }
    FastLED.show();
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
