#ifndef MIDICommand_h
#define MIDICommand_h
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class MIDICommand {
    public:
        int Command;
        int ParamOne;
        int ParamTwo;
        static int NOTEON;
        static int NOTEOFF;
        static int PITCHBEND;
        static int CONTROL;

        MIDICommand(int command, int paramOne, int paramTwo);
};

#endif