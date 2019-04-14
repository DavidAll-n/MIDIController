#ifndef MIDIController_h
#define MIDIController_h
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "ShiftRegister.h"
#include "ControlOut.h"
#include "MIDICommand.h"

class MIDIController {
    private:
        int VelocityPin;
        int OctaveUpPin;
        int OctaveDownPin;
        ShiftRegister registers[8];
        ControlOut controls[12];
        byte MaxOctave;

        void SendMIDI(MIDICommand command);
        void OctaveUp();
        void OctaveDown();
    
    public:
        byte Octave;
        MIDIController();
        void UpdateRegisters(long debounceIn);
        ShiftRegister* GetRegisters();
        ControlOut* GetControls();
        void UpdateRegister(int index, long debounceIn);
        void UpdateControl(int index);
        void UpdateControls();
        int GetVelocity();
};

#endif