#ifndef RigStick_h
#define RigStick_h

#include "Arduino.h"
#include "Joystick.h"

enum InputType {
  TRG = 0,
  HAT,
  DMS
}; 


class RigStick
{
  public:
    RigStick(bool debug);
    byte shiftIn(int myDataPin, int myClockPin);
    boolean getBit(byte myVarIn, int whatBit);
    byte setBit(byte myVarIn, byte whatBit, boolean s);
    void read(byte  input, InputType type, Joystick_ stick );
    void setDebug(bool debug);
    
    private:
    bool _debug;
    int getButtonNumber(InputType type, int index);
    String getButtonName(InputType type, int index);
    bool _currentStateTrg[8] = {1};
    bool _currentStateHat[8] = {1};
    bool _currentStateDms[8] = {1};
    bool _currentState[3][8] = {{0, _currentStateTrg}, {1,_currentStateHat }, {2, _currentStateDms}};
};

#endif

