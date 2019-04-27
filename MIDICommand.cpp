#include "MIDICommand.h"

MIDICommand::MIDICommand(int command, int paramOne, int paramTwo) {
    Command = command;
    ParamOne = paramOne;
    ParamTwo = paramTwo;
}