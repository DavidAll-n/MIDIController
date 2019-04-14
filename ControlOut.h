#ifndef ControlOut_h
#define ControlOut_h
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "MIDICommand.h"

class ControlOut {
    int previousOutputValue;
    int inputSelect;
    int controller;
    int command;
    int sensorValue;
    int outputValue;
    int* returnValue;

  public:
    ControlOut();
    void Initialize(int commandIn, int inputSelectIn, int controllerNum);
    int* Update();
};

#endif