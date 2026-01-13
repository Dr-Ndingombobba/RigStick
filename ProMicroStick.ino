
#include "ProMicroStickLib.h"
#include "Joystick.h"


Joystick_ Joystick;

ProMicroStickLib stick(false);

// Flightstick pinout
int latchPin = 8;
int dataPin = 9;
int clockPin = 7;

byte trgByte = 0b11111111;
byte hatByte = 0b11111111;
byte dmsByte = 0b11111111;

// Throttle
int throttlePin = A0;
int maxThrottle = 536;
int minThrottle = 30;
int throttlePos = 0;

// X-axis
int xAxisPin = A1;
int maxX = 950;
int minX = 100;
int xPos = 0;


// Y-axis
int yAxisPin = A2;
int maxY = 800;
int minY = 130;
int yPos = 0;


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

  digitalWrite(LED_BUILTIN, 0);

  // Stick button operation
  digitalWrite(latchPin, 1);
  delayMicroseconds(20);
  digitalWrite(latchPin, 0);

  trgByte = stick.shiftIn(dataPin, clockPin);
  hatByte = stick.shiftIn(dataPin, clockPin);
  dmsByte = stick.shiftIn(dataPin, clockPin);

  stick.interpret(trgByte, 0, Joystick);
  stick.interpret(hatByte, 1, Joystick);
  stick.interpret(dmsByte, 2, Joystick);

  // Thottle
  throttlePos = maxThrottle - analogRead(throttlePin); // invert
  Joystick.setThrottle(throttlePos);

  // X-Axis
  xPos = analogRead(xAxisPin); 
  Joystick.setXAxis(xPos);

  // Y-Axis
  yPos = analogRead(yAxisPin); 
  Joystick.setYAxis(yPos);

  //Serial.println("throttlePos: " + String(throttlePos) );
  Joystick.sendState();
  delay(50);
}
