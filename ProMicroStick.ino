
#include "ProMicroStickLib.h"
#include "Joystick.h"


Joystick_ Joystick;

ProMicroStickLib stick(false);

int latchPin = 8;
int dataPin = 9;
int clockPin = 7;
int throttlePin = A0; // 0 -> 1023 
int maxThrottle = 1023;
int minThrottle = 0;
int throttlePos = 0;

byte trgByte = 0b11111111;
byte hatByte = 0b11111111;
byte dmsByte = 0b11111111;


void setup() {

  Serial.begin(9600);

  pinMode(latchPin, OUTPUT);

  pinMode(clockPin, OUTPUT);

  pinMode(dataPin, INPUT);

  Joystick.setThrottleRange(0, 1023);

  Joystick.begin(false);
}

void loop() {

  digitalWrite(LED_BUILTIN, 0);
  digitalWrite(latchPin, 1);
  delayMicroseconds(20);
  digitalWrite(latchPin, 0);

  trgByte = stick.shiftIn(dataPin, clockPin);
  hatByte = stick.shiftIn(dataPin, clockPin);
  dmsByte = stick.shiftIn(dataPin, clockPin);

  stick.interpret(trgByte, 0, Joystick);
  stick.interpret(hatByte, 1, Joystick);
  stick.interpret(dmsByte, 2, Joystick);

  throttlePos = maxThrottle - analogRead(throttlePin);
  Joystick.setThrottle(throttlePos);

  Joystick.sendState();
  delay(50);
}
