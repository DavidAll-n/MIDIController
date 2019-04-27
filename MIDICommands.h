#ifndef MIDICommands_h
#define MIDICommands_h

enum MIDICommands {
    NOTEON = 0x90,
    NOTEOFF = 0x80,
    PITCHBEND = 0xE0,
    CONTROL = 0xB0
};

#endif