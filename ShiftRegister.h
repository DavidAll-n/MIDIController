/*
 * Class ShiftRegister creates allows easy reading of shift registers
 * over SPI
 * 
 * Author: David Allen
 */

#ifndef ShiftRegister_h
#define ShiftRegister_h
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "Note.h"

class ShiftRegister {

  public:
    ShiftRegister();
    ShiftRegister(int ssPinIn, int regMultiplierIn, int stepsIn);
    Note * Update(long debounceIn, int octaveMultiplier);
    void Initialize(int ssPinIn, int regMultiplierIn, int stepsIn);

  private:
    int ssPin;
    int regMultiplier;
    int prevVal;
    int curVal;
    int resVal;
    int curArray[8];
    int resArray[8];
    int steps;
    long lastDebounceTime;
    long debounceTime;
    Note* notes;
};

#endif