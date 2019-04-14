#include "ControlOut.h"

#define PIN_MUX_IN A5

ControlOut::ControlOut() {
}

void ControlOut::Initialize(int commandIn, int inputSelectIn, int controllerNum) {
    command = commandIn;
    inputSelect = inputSelectIn;
    controller = controllerNum;
}

int* ControlOut::Update() {
    switch (inputSelect) {
        case 0:
          PORTC = B00000000;
          break;
        case 1:
          PORTC = B00000001;
          break;
        case 2:
          PORTC = B00000010;
          break;
        case 3:
          PORTC = B00000011;
          break;
        case 4:
          PORTC = B00000100;
          break;
        case 5:
          PORTC = B00000101;
          break;
        case 6:
          PORTC = B00000110;
          break;
        case 7:
          PORTC = B00000111;
          break;
        case 8:
          PORTC = B00001000;
          break;
        case 9:
          PORTC = B00001001;
          break;
        case 10:
          PORTC = B00001010;
          break;
        case 11:
          PORTC = B00001011;
          break;
        case 12:
          PORTC = B00001100;
          break;
        case 13:
          PORTC = B00001101;
          break;
        case 14:
          PORTC = B00001110;
          break;
        case 15:
          PORTC = B00001111;
          break;
      }

      sensorValue = analogRead(PIN_MUX_IN);
      outputValue = map(sensorValue, 0, 1023, 0, 127);
      if (outputValue != previousOutputValue) {
        returnValue[0] = command;
        returnValue[1] = controller;
        returnValue[2] = outputValue;
      }
      else {
        returnValue[0] = -1;
        returnValue[1] = -1;
        returnValue[2] = -1;
      }
      previousOutputValue = outputValue;
      return returnValue;
}