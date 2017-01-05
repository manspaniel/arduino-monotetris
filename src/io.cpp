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
  unsigned char byte;
  for(int16_t k = 0; k < len; k++) {
    byte = pgm_read_byte_near(str + k);
    display->drawChar(x + k * 6, y, byte, color, bg, 1);
  }
  
}

void drawDialog(Display * display, const char * str, int x, int y, int width, int height) {
  
  display->drawFastHLine(x + 1, y, width - 1, BLACK);
  display->drawFastHLine(x + 1, y + height, width - 1, BLACK);
  display->drawFastHLine(x + 2, y + height + 1, width - 1, BLACK);
  
  display->drawFastVLine(x, y + 1, height, BLACK);
  display->drawFastVLine(x + width, y + 1, height, BLACK);
  display->drawFastVLine(x + width + 1, y + 2, height - 1, BLACK);
  
  display->fillRect(x + 1, y + 1, width - 1, 13, BLACK);
  display->fillRect(x + 1, y + 13, width - 1, height - 13, WHITE);
  
  int16_t len = strlen_P(str);
  unsigned char byte;
  for(int16_t k = 0; k < len; k++) {
    byte = pgm_read_byte_near(str + k);
    display->drawChar(x + 4 + k * 6, y + 3, byte, WHITE, BLACK, 1);
  }
  
}