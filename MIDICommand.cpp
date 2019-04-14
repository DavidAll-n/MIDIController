#include "MIDICommand.h"

int MIDICommand::NOTEON = 0x90;
int MIDICommand::NOTEOFF = 0x80;
int MIDICommand::PITCHBEND = 0xE0;
int MIDICommand::CONTROL = 0xB0;

MIDICommand::MIDICommand(int command, int paramOne, int paramTwo) {
    Command = command;
    ParamOne = paramOne;
    ParamTwo = paramTwo;
}