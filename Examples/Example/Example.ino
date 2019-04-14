#include <MIDICommand.h>
#include <MIDIController.h>
#include <Note.h>
#include <ShiftRegister.h>
#include <ControlOut.h>
#include <SPI.h>

MIDIController MIDI = MIDIController();

void setup() {
  Serial.begin(31250);  //for MIDI
  //Serial.begin(9600); //for debugging
  DDRC = B00001111; //Sets analog pins as appropiate ins/outs
  DDRD = DDRD | B11111100; //Sets Digital Pins 0-7 to appropriate ins/out
  DDRB = DDRB | B00101111;  //Sets Digial Pins 8-13 to appropriate ins/outs
  SPI.begin();
}

void loop() {
  ShiftRegister* registers = MIDI.GetRegisters();
  for (int i = 0; i < sizeof(registers); i++) {
    MIDI.UpdateRegister(i, millis());
  }

  ControlOut* controls = MIDI.GetControls();
  for (int i = 0; i < sizeof(controls); i++) {
    MIDI.UpdateControl(i);
  }
}
