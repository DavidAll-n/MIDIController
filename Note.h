#ifndef Note_h
#define Note_h
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class Note {
    public:
        int NoteNumber;
        int Value;

        Note(int note, int value);
};

#endif