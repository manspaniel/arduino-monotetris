#include "io.h"
#include <avr/pgmspace.h>
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

void drawProgString(Display * display, int16_t x, int16_t y, const char * str, uint16_t color, uint16_t bg) {
  
  int16_t len = strlen_P(str);
  for(int16_t k = 0; k < len; k++) {
    display->drawChar(x + k * 6, y, pgm_read_byte_near(str + k), color, bg, 1);
  }
  
}