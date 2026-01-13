
#include "Arduino.h"
#include "RigStick.h"
#include "joystick.h"


String trgByteButtons[8] = {

  "trigger 2",       // 0
  "side",            // 1
  "lever",           // 2
  "pinky",           // 3
  "release",         // 4
  "nothing 5",       // 5
  "trigger 1 full",  // 6
  "trigger 1"        // 7
};

int trgIntButtons[8] = {

  7,
  6,
  5,
  4,
  3,
  2,
  1,
  0
};

String hatByteButtons[8] = {

  "tms L",           // 0
  "tms DN",          // 1
  "tms R",           // 2
  "tms UP",          // 3
  "trim hat left",   // 4
  "trim hat down",   // 5
  "trim hat right",  // 6
  "trim hat up"      // 7
};

int hatIntButtons[8] = {

  15,
  14,
  13,
  12,
  11,
  10,
  9,
  8
};


String dmsByteButtons[8] = {

  "cms L",   // 0
  "cms DN",  // 1
  "cms R",   // 2
  "cms UP",  // 3
  "dms L",   // 4
  "dms DN",  // 5
  "dms R",   // 6
  "dms UP"   // 7
};

int dmsIntButtons[8] = {

  23,
  22,
  21,
  20,
  19,
  18,
  17,
  16
};



RigStick::RigStick(bool debug) {

  _debug = debug;
}


byte RigStick::shiftIn(int myDataPin, int myClockPin) {

  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);

  pinMode(myDataPin, INPUT);

  for (i = 7; i >= 0; i--) {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(2);
    temp = digitalRead(myDataPin);

    if (temp) {
      pinState = 1;
      myDataIn = myDataIn | (1 << i);
    } else {
      pinState = 0;
    }

    digitalWrite(myClockPin, 1);
  }

  return myDataIn;
}

boolean RigStick::getBit(byte myVarIn, int whatBit) {

  return ((myVarIn >> whatBit) & 0x01);
}

byte RigStick::setBit(byte myVarIn, byte whatBit, boolean s) {

  if (s) {
    myVarIn = myVarIn | (1 << whatBit);
  } else {
    myVarIn = myVarIn & ~(1 << whatBit);
  }

  return myVarIn;
}

int RigStick::getButtonNumber(InputType type, int index) {

  switch (type) {
    case TRG:
      return trgIntButtons[index];
      break;
    case HAT:
      return hatIntButtons[index];
      break;
    case DMS:
      return dmsIntButtons[index];
      break;
    default:
      return -1;
  };
}

String RigStick::getButtonName(InputType type, int index) {

  switch (type) {
    case TRG:
      return (trgByteButtons[index]);
      break;
    case HAT:
      return (hatByteButtons[index]);
      break;
    case DMS:
      return (dmsByteButtons[index]);
      break;
    default:
      return ("unmapped, type " + String(type) + " index " + String(index));
  };
}


void RigStick::read(byte input, InputType type, Joystick_ stick) {
  String action = "";

  for (int n = 0; n <= 7; n++) {
    bool state = this->getBit(input, n);

    if (state != _currentState[type][n]) {

      int button = this->getButtonNumber(type, n);
      if (state) {
        action = "released";
        stick.releaseButton(button);
      } else {
        action = "pressed";
        stick.pressButton(button);
      }
      if (_debug) Serial.println(this->getButtonName(type, n) + " " + action);

      _currentState[type][n] = state;
    }
  }
}

void RigStick::setDebug(bool debug) {
  _debug = debug;
}
