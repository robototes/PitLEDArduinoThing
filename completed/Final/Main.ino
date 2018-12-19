#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 6
#define hueRes NUM_LEDS


CRGB leds[NUM_LEDS];

CRGB RED = CRGB(255, 0, 0);
CRGB GREEN = CRGB(0, 255, 0);
CRGB BLUE = CRGB(0, 0, 255);
CRGB YELLOW = CRGB(255 / 2, 255 / 2, 0);
CRGB ORANGE = CRGB(255, 40, 0);
CRGB CYAN = CRGB(0, 255, 200);
CRGB PURPLE = CRGB(255 / 2, 0, 255 / 3);
CRGB BLACK = CRGB(0, 0, 0);
CRGB WHITE = CRGB(255, 255, 255);

CRGB CONSTCOLORS[8] = {
  RED, GREEN, BLUE, YELLOW, ORANGE, CYAN, PURPLE, WHITE
};


CRGB GOODCOLORS[6][3] = {
  {GREEN, BLUE, NULL}, {RED, BLACK, NULL}, {RED, WHITE, NULL}, {WHITE, BLACK, NULL}, {PURPLE, YELLOW, NULL}, {RED, WHITE, BLUE}
};



CRGB hueColors[hueRes];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < hueRes; i += 1) {
    hueColors[i] = calculateRGB(map(i, 0, hueRes, 0, 360));
  }
}




void loop()
{
  pickRandomFunction();
}

void fillAll(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
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
    CRGB color = calculateRGB(i);
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = color;
    }
    FastLED.show();
    delay(d);
  }
}


void HSVSwirl(int d, int repeat) { // colors to display, delay between movement, number of times each color shows up. try to make colors * repeat  = 144.
  for (int i = 0; i < NUM_LEDS; i++) { // one rotation
    for (int k = 0 ; k < repeat; k++) {
      for (int j = 0; j < NUM_LEDS / repeat; j += 1) { //this loop jumps to the start of each new color segment by that length
        //leds[(i + j + k * NUM_LEDS / repeat) % NUM_LEDS] = calculateRGB((double)map(j, 0, NUM_LEDS / repeat, 0, 360));
        leds[(i + j + k * NUM_LEDS / repeat) % NUM_LEDS] = hueColors[(int)map(j, 0, NUM_LEDS / repeat, 0, hueRes)];
      }
    }
    FastLED.show();
    delay(d);
  }
}

CRGB calculateRGB(double angle) {

  if (angle < 0) {
    angle = 0;
  }

  double l = 0.5;
  double s = 1.0;

  double temp1 = l + s - l * s;
  double temp2 = 2.0 * l - temp1;

  double hue = angle / 360.0;
  double tempRed = hue + 0.333;
  double tempGreen = hue;
  double tempBlue = hue - 0.333;

  if (tempRed > 1) {
    tempRed -= 1;
  }

  if (tempBlue < 0) {
    tempBlue += 1;
  }

  double red = 0;
  Serial.println(tempRed);
  if (6 * tempRed < 1) {
    red = temp2 + (temp1 - temp2) * 6.0 * tempRed;
  } else if (2 * tempRed < 1) {
    red = temp1;
  } else if (3 * tempRed < 2 ) {
    red = temp2 + (temp1 - temp2) * (0.666 - tempRed) * 6.0;
  } else {
    red = temp2;
  }

  double green = 0;

  if (6 * tempGreen < 1) {
    green = temp2 + (temp1 - temp2) * 6.0 * tempGreen;
  } else if (2 * tempGreen < 1) {
    green = temp1;
  } else if (3 * tempGreen < 2 ) {
    green = temp2 + (temp1 - temp2) * (0.666 - tempGreen) * 6.0;
  } else {
    green = temp2;
  }

  double blue = 0;

  if (6 * tempBlue < 1) {
    blue = temp2 + (temp1 - temp2) * 6.0 * tempBlue;
  } else if (2 * tempBlue < 1) {
    blue = temp1;
  } else if (3 * tempBlue < 2 ) {
    blue = temp2 + (temp1 - temp2) * (0.666 - tempBlue) * 6.0;
  } else {
    blue = temp2;
  }
  return CRGB(red * 255, green * 255, blue * 255);

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
    FastLED.show();
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
    FastLED.show();
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
      FastLED.show();
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
      leds[(center - dot+NUM_LEDS) % NUM_LEDS] = CRGB(red, green, blue);
    } else {
      leds[(center - dot) % NUM_LEDS] = CRGB(red, green, blue);
    }

    FastLED.show();
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
    FastLED.show();
  }
}
