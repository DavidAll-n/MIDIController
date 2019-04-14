#include "MIDIController.h"
#include "ShiftRegister.h"
#include "MIDICommand.h"

#define PIN_SS1          2
#define PIN_SS2          3
#define PIN_SS3          4
#define PIN_SS4          5
#define PIN_SS5          6
#define PIN_SS6          7
#define PIN_SS7          8
#define PIN_SS8          9
#define PIN_SS9          10

void MIDIController::SendMIDI(MIDICommand command) {
    Serial.write(command.Command);
    Serial.write(command.ParamOne);
    Serial.write(command.ParamTwo);
}

void MIDIController::OctaveUp() {
    if (Octave < MaxOctave) {
        Octave++;
    }
}

void MIDIController::OctaveDown() {
    if (Octave > 0) {
        Octave--;
    }
}

MIDIController::MIDIController() {
    Octave = 4;
    MaxOctave = 7;
    VelocityPin = A3;
    OctaveUpPin = 11;
    OctaveDownPin = 10;
    registers[0].Initialize(PIN_SS1, 2, 8);
    registers[1].Initialize(PIN_SS2, 3, 8);
    registers[2].Initialize(PIN_SS3, 4, 8);
    registers[3].Initialize(PIN_SS4, 1, 8);
    registers[4].Initialize(PIN_SS5, 5, 8);
    registers[5].Initialize(PIN_SS6, 6, 8);
    registers[6].Initialize(PIN_SS7, 7, 8);
    registers[7].Initialize(PIN_SS8, 8, 8);
    
    controls[0].Initialize(MIDICommand::CONTROL, 1, 1); // Mod
    controls[1].Initialize(MIDICommand::CONTROL, 2, 10); // Pan
    controls[2].Initialize(MIDICommand::CONTROL, 3, 11); // Expression
    controls[3].Initialize(MIDICommand::CONTROL, 4, 71); // Resonance
    controls[4].Initialize(MIDICommand::CONTROL, 5, 72); // Decay
    controls[5].Initialize(MIDICommand::CONTROL, 6, 73); // Attack
    controls[6].Initialize(MIDICommand::CONTROL, 7, 74); // Frequency
    controls[7].Initialize(MIDICommand::CONTROL, 8, 80); // Tone One
    controls[8].Initialize(MIDICommand::CONTROL, 9, 81); // Tone Two
    controls[9].Initialize(MIDICommand::CONTROL, 10, 82); // Tone Three
    controls[10].Initialize(MIDICommand::CONTROL, 11, 83); // Tone Four
    controls[11].Initialize(MIDICommand::PITCHBEND, 12, 127); // Pitch Bend
}

ShiftRegister* MIDIController::GetRegisters() {
    return registers;
}

ControlOut* MIDIController::GetControls() {
    return controls;
}

void MIDIController::UpdateControl(int index) {
    int* returnValue = controls[index].Update();
    if (returnValue[0] != -1) {
        MIDICommand command = MIDICommand(returnValue[0], returnValue[1], returnValue[2]);
        SendMIDI(command);
    }
}

void MIDIController::UpdateRegister(int index, long debounceIn) {
    Note* notes = registers[index].Update(debounceIn, Octave);
    for(int p = 0; p < sizeof(notes); p++) {
        MIDICommand command = MIDICommand(MIDICommand::NOTEON, notes[p].NoteNumber, GetVelocity());
        
        if (notes[p].Value == 1) {
            command.Command = MIDICommand::NOTEOFF;
        }

        SendMIDI(command);
    }
}

void MIDIController::UpdateRegisters(long debounceIn) {
    for(int i = 0; i < sizeof(registers); i++) {
        Note* notes = registers[i].Update(debounceIn, Octave);
        for(int p = 0; p < sizeof(registers); p++) {
            
            MIDICommand command = MIDICommand(MIDICommand::NOTEON, notes[p].NoteNumber, GetVelocity());
            
            if (notes[p].Value == 1) {
            command.Command = MIDICommand::NOTEOFF;
            }

            SendMIDI(command);
        }
    }
}

int MIDIController::GetVelocity() {
    int velocity = analogRead(VelocityPin);
    velocity = map(velocity, 0, 1023, 32, 127);
    return velocity;
}