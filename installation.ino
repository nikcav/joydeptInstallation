#include <Adafruit_NeoPixel.h>
#define PIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800); //ring light

int fsrAnalogPin = 0; // pressure sensor
int fsrReading;      // pressure reading from the FSR
int pin8 = 8; //small LED 1
int pin7 = 7; //small LED 2
int redPin = 6; //RGB 1
int greenPin = 5; //RGB 1
int bluePin = 3; //RGB 1
int redPin2 = 11; //RGB 2
int greenPin2 = 10; //RGB 2
int bluePin2 = 9; //RGB2

void setup(void) {

  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(200);
  strip.show(); //lines 19-22 setup ring light
  pinMode(pin8, OUTPUT);
  pinMode(pin7, OUTPUT); //lines 23-24 setup small LEDs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT); //lines 25-30 setup RGBs
}

void loop(void) {
  fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Pressure = ");
  Serial.println(fsrReading); //collects and prints pressure reading

  if (fsrReading > 30) { //if pressure is above 30
    digitalWrite(pin8, HIGH);
    digitalWrite(pin7, HIGH); //turn on small LEDs
    setColor(250, 50, 0); //turn on RGB to orange
    colorWipe(strip.Color(255, 0, 0));
    colorWipe(strip.Color(250, 50, 0));
    colorWipe(strip.Color(242, 110, 0));
    colorWipe(strip.Color(255, 255, 0));
    colorWipe(strip.Color(0, 255, 0));
    colorWipe(strip.Color(0, 255, 255));
    colorWipe(strip.Color(0, 0, 255));
    colorWipe(strip.Color(200, 0, 150)); //turn on ring light and cycle through different colors
  }

  delay(100);

  colorWipe(strip.Color(0, 0, 0));
  digitalWrite(pin8, LOW);
  digitalWrite(pin7, LOW);
  setColor(0 , 0, 0); //turn off all the lights
  delay(100);
}

void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(50);
  }
}

void setColor(int red, int green, int blue) {
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  analogWrite(redPin2, red);
  analogWrite(greenPin2, green);
  analogWrite(bluePin2, blue);
}
