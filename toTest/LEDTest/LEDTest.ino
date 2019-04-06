#include <FastLED.h>
#define NUM_LEDS 36
#define DATA_PIN 5
#define NUM_STRANDS 15

CRGB CONSTCOLORS[8] = {
  CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Orange, CRGB::Cyan, CRGB::Purple, CRGB::White
};


CRGB GOODCOLORS[6][3] = {
  {CRGB::Green, CRGB::Blue, NULL}, {CRGB::Red, CRGB::Black, NULL}, {CRGB::Red, CRGB::White,CRGB::Black }, {CRGB::White, CRGB::Black, NULL}, {CRGB::Purple, CRGB::Yellow, NULL}, {CRGB::Red, CRGB::White, CRGB::Blue}
};

const char *colors[2] = {
  "G",
  "B"
};

const char *colorValues[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  CRGB color = CONSTCOLORS[random(sizeof(CONSTCOLORS)/sizeof(CONSTCOLORS[0]))];
//  Serial.println(sizeof(CONSTCOLORS)/sizeof(CONSTCOLORS[0]));
  Serial.println(color.red);
  Serial.println(color.green);
  Serial.println(color.blue);
  */
//  CRGB colors[3] = GOODCOLORS[random(sizeof(GOODCOLORS)/sizeof(GOODCOLORS[0]))];
//  for(int i = 0; i < 3; i++) {
//    CRGB color = colors[i];
//    Serial.println(color.red);
//    Serial.println(color.green); 
//    Serial.println(color.blue);
//  }
  testSwirl(2, 1000, 2);
}

void fakeShow() {
  Serial.print("{");
  for(int i = 0; i < NUM_LEDS; i++) {
    Serial.print(colorValues[i]);
    Serial.print(", ");
  }
  Serial.print("}\n");
}

void testSwirl(int numColors,  int d, int repeat) {
  int segmentLength = (int) floor(NUM_LEDS / (numColors * repeat));
  for(int startingLEDIndex = 0; startingLEDIndex < NUM_LEDS; startingLEDIndex++) { // The index of the LED where the first color segment starts.
    int colorIndex = 0; // The index of the current color we're using.
    int lastTransitionLEDIndex = startingLEDIndex; // The index of the LED in between the segments (where the strip changes color).
    for(int i = startingLEDIndex; i < startingLEDIndex + NUM_LEDS; i++) {
      int scaledIndex = i % NUM_LEDS; // Rescale so we loop back around to the beginning if startingLEDIndex is greater than zero.
//      Serial.print("Scaled index"); Serial.println(scaledIndex);
      if(i - lastTransitionLEDIndex == segmentLength) { // New segment
//        Serial.println("New segment");
        colorIndex = (colorIndex + 1) % numColors;
//        Serial.print("Color index: "); Serial.println(colorIndex);
        lastTransitionLEDIndex = i;
//        Serial.print("Last transitionLEDIndex: "); Serial.println(lastTransitionLEDIndex);
      }
      colorValues[scaledIndex] = colors[colorIndex];
    }
//    Serial.println("----------------");
    delay(d);
    fakeShow();
  }
}
