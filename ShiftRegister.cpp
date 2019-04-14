/*
 * Class ShiftRegister creates allows easy reading of shift registers
 * over SPI
 * 
 * Author: David Allen
 */

#include "ShiftRegister.h"
#include "Note.h"
#include <SPI.h>

ShiftRegister::ShiftRegister() {
    debounceTime = 50;
}

ShiftRegister::ShiftRegister(int ssPinIn, int regMultiplierIn, int stepsIn) {
    ssPin = ssPinIn;
    regMultiplier = regMultiplierIn;
    steps = stepsIn;
    debounceTime = 50;
    digitalWrite(ssPin, HIGH);
}

void ShiftRegister::Initialize(int ssPinIn, int regMultiplierIn, int stepsIn){
    ssPin = ssPinIn;
    regMultiplier = regMultiplierIn;
    steps = stepsIn;
};

Note* ShiftRegister::Update(long debounceIn, int octaveMultiplier) {
            if ((debounceIn - lastDebounceTime) > debounceTime) {
                SPI.beginTransaction(SPISettings(3500000, MSBFIRST, SPI_MODE0));
                digitalWrite(ssPin, LOW); //toggle ss pin to shift register
                curVal = SPI.transfer(0x00);  //grab the data from the shift register starting at address 0x00
                
                /*
                * Bitwise XOR previous value and current value to see which bits have changed
                * 
                * 00101001
                * XOR
                * 10100111
                * =
                * 10001110
                */
                resVal = curVal ^ prevVal;

                
                for (int i = 0; i < steps; ++i) {  //read the bits from the current value and the result value into arrays
                    resArray[i] = bitRead(resVal, i);
                    curArray[i] = bitRead(curVal, i);
                }
                prevVal = curVal;
                
                for (int i = 0; i < steps; ++i) {  //read the arrays and calculate the notes to turn on and off
                
                    int note = (i + (regMultiplier * 8)) + (octaveMultiplier * 12); //each register will return 1 - 8, each register has a calculable offset (register number * number/register), this combined with the octave offset will return our note number
                    
                    if (resArray[i] != 0 && curArray[i] == 1) {  //if the note has changed (ie the bit in the resValue is not 0), and the current
                        notes[i] = Note(note, 1);
                    }
                    else if (resArray[i] != 0 && curArray[i] == 0) {
                        notes[i] = Note(note, 0);
                    }
                }
                digitalWrite(ssPin, HIGH);
                SPI.endTransaction();
                lastDebounceTime = debounceIn;
                return notes;
            }
        }