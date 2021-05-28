#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUM_LEDS 32
#define BUTTON_1 6
#define BUTTON_2 7
#define BUTTON_3 8
#define BUTTON_4 9
#define MAX_STEPS 10
#define MAX_REAL_INTENSE 150


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int intense = 10;
int real_intense = MAX_REAL_INTENSE;
int red = 10;
int green = 10;
int blue = 10;
int real_red = MAX_REAL_INTENSE;
int real_green = MAX_REAL_INTENSE;
int real_blue = MAX_REAL_INTENSE;

void setup() {
  strip.begin();
  strip.show();
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_4) == LOW) {
    intense = intense + 1;
    if ( intense > MAX_STEPS ) {
      intense = 0;
    }
    real_intense = map(intense, 0, MAX_STEPS, 10, MAX_REAL_INTENSE);
  }

  if (digitalRead(BUTTON_3) == LOW) {
    blue = blue + 1;
    if ( blue > MAX_STEPS ) {
      blue = 0;
    }
  }

  if (digitalRead(BUTTON_2) == LOW) {
    green = green + 1;
    if ( green > MAX_STEPS ) {
      green = 0;
    }
  }

  if (digitalRead(BUTTON_1) == LOW) {
    red = red + 1;
    if ( red > MAX_STEPS ) {
      red = 0;
    }
  }

  real_red = map(red, 0, MAX_STEPS, 0, real_intense);
  real_green = map(green, 0, MAX_STEPS, 0, real_intense);
  real_blue = map(blue, 0, MAX_STEPS, 0, real_intense);
  
  // put your main code here, to run repeatedly:
  // set pixel to red, delay(1000)
  // for (int i = 0; i <= NUM_LEDS; i++) {
  //   strip.setPixelColor(i, real_intense, 0, 0);
  // }
  // strip.show();
  // delay(100);
  // set pixel to off, delay(1000)
  for (int i = 0; i <= NUM_LEDS; i++) {
    strip.setPixelColor(i, real_red, real_green, real_blue);
  }
  strip.show();
  delay(100);
}
