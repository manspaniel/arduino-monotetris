#include "io.h"
#include <Arduino.h>

Display * getMainDisplay() {
  return &display;
}

void initButtons() {
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_L, INPUT_PULLUP);
  pinMode(BUTTON_R, INPUT_PULLUP);
}

bool isButtonDown(int buttonID) {
  if(digitalRead(buttonID) == LOW) {
    return true;
  } else {
    return false;
  }
}