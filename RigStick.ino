
#include "RigStick.h"
#include "Joystick.h"


int debug = 0;
Joystick_ Joystick;
RigStick stick(debug);

int debugPin = 3;
int clockPin = 7;
int latchPin = 8;
int dataPin = 9;

int throttlePin = A0;
int xAxisPin = A1;
int yAxisPin = A2;

byte trgByte = 0b11111111;
byte hatByte = 0b11111111;
byte dmsByte = 0b11111111;

int maxThrottle = 536;
int minThrottle = 30;
int throttlePos = 0;

int maxX = 950;
int minX = 100;
int xPos = 0;


int maxY = 800;
int minY = 130;
int yPos = 0;
int RXLED = 17;


void setup() {

  Serial.begin(9600);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
  Joystick.setThrottleRange(minThrottle, maxThrottle);
  Joystick.setXAxisRange(minX, maxX);
  Joystick.setYAxisRange(minY, maxY);

  Joystick.begin(false);
}

void loop() {

  digitalWrite(latchPin, 1);
  delayMicroseconds(20);
  digitalWrite(latchPin, 0);

  trgByte = stick.shiftIn(dataPin, clockPin);
  hatByte = stick.shiftIn(dataPin, clockPin);
  dmsByte = stick.shiftIn(dataPin, clockPin);

  throttlePos = analogRead(throttlePin);  // invert
  xPos = analogRead(xAxisPin);
  yPos = analogRead(yAxisPin);
  debug = digitalRead(debugPin);

  if (debug != LOW) {
    // debug mode
    stick.setDebug(true);
    print(trgByte, hatByte, dmsByte, throttlePos, xPos, yPos);

    stick.read(trgByte, 0, Joystick);
    stick.read(hatByte, 1, Joystick);
    stick.read(dmsByte, 2, Joystick);
    
    delay(50);
  } 
  else {
    stick.setDebug(false);
    Serial.println("operation....");

    // update pc
    stick.read(trgByte, 0, Joystick);
    stick.read(hatByte, 1, Joystick);
    stick.read(dmsByte, 2, Joystick);

    Joystick.setThrottle(throttlePos);
    Joystick.setXAxis(xPos);
    Joystick.setYAxis(yPos);
    Joystick.sendState();
    delay(50);
  }
}

void print(int trgByte, int hatByte, int dmsByte, int throttlePos, int xPos, int yPos) {
  Serial.println(  " th: " + String(throttlePos) + " x: " + String(xPos) + " y:  " + String(yPos));
}
