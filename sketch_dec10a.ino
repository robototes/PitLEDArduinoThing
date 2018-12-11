#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

CRGB RED = CRGB(255,0,0);
CRGB GREEN = CRGB(0,255,0);
CRGB BLUE = CRGB(0,0,255);
CRGB YELLOW = CRGB(255,255,0);
CRGB ORANGE = CRGB(255,100,0);
CRGB CYAN = CRGB(0,255,255);
CRGB PURPLE = CRGB(255,0,255);
CRGB BLACK = CRGB(0,0,0);
CRGB WHITE = CRGB(255,255,255);

CRGB CONSTCOLORS[9] = {
  RED, GREEN, BLUE, YELLOW, ORANGE, CYAN, PURPLE, BLACK, WHITE 
};


void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{

  pickRandomFunction();

}

void pickRandomFunction(){
  int randomPick = random(0,3);
  if(randomPick == 0){
    HSVFill(30);
  }else if(randomPick == 1){
    HSVSwirl(0,(int)random(1,3));
  }else if(randomPick == 2){
    int swirlLength = random(2,6);
    if(swirlLength == 5){
      swirlLength = 6;
    }
    CRGB swirlColors[swirlLength] = {};
    for(int i = 0; i < swirlLength; i++){
      swirlColors[i] = random(CONSTCOLORS);
    }
    swirl(swirlColors,swirlLength, 30, random(1,3));
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
        leds[(i + j + k * NUM_LEDS / repeat) % NUM_LEDS] = calculateRGB((double)map(j, 0, NUM_LEDS / repeat, 0, 360));
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
