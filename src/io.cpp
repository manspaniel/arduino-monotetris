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

static unsigned long lastButtonA = 0;
static unsigned long lastButtonB = 0;
static unsigned long lastButtonL = 0;
static unsigned long lastButtonR = 0;

bool isButtonDown(int buttonID) {
  if(digitalRead(buttonID) == LOW) {
    return true;
  } else {
    return false;
  }
}

bool isButtonDown(int buttonID, unsigned long debounce) {
  int lastTime = 0;
  if(buttonID == BUTTON_A) {
    lastTime = lastButtonA;
  } else if(buttonID == BUTTON_B) {
    lastTime = lastButtonB;
  } else if(buttonID == BUTTON_L) {
    lastTime = lastButtonL;
  } else if(buttonID == BUTTON_R) {
    lastTime = lastButtonR;
  }
  bool buttonIsDown = digitalRead(buttonID) == LOW;
  if(buttonIsDown && millis() - lastTime > debounce) {
    // Button is down and in debounce range
    if(buttonID == BUTTON_A) {
      lastButtonA = millis();
    } else if(buttonID == BUTTON_B) {
      lastButtonB = millis();
    } else if(buttonID == BUTTON_L) {
      lastButtonL = millis();
    } else if(buttonID == BUTTON_R) {
      lastButtonR = millis();
    }
    return true;
  } else if(!buttonIsDown) {
    // Button is not down at all. Wipe last button time, so it'll be triggered instantly next time
    if(buttonID == BUTTON_A) {
      lastButtonA = 0;
    } else if(buttonID == BUTTON_B) {
      lastButtonB = 0;
    } else if(buttonID == BUTTON_L) {
      lastButtonL = 0;
    } else if(buttonID == BUTTON_R) {
      lastButtonR = 0;
    }
  }
  return false;
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

  display->drawFastVLine(x, y + 1, height - 1, BLACK);
  display->drawFastVLine(x + width, y + 1, height, BLACK);
  display->drawFastVLine(x + width + 1, y + 2, height - 1, BLACK);
  
  display->fillRect(x + 1, y + 1, width - 1, 13, BLACK);
  display->fillRect(x + 1, y + 13, width - 1, height - 13, WHITE);
  
  int16_t len = strlen_P(str);
  unsigned char byte;
  for(int16_t k = 0; k < len; k++) {
    byte = pgm_read_byte_near(str + k);
    display->drawChar(x + 13 + k * 6, y + 3, byte, WHITE, BLACK, 1);
  }
  
  int closeX = x + 2;
  int closeY = y + 2;
  
  display->fillRoundRect(closeX, closeY, 9, 9, 1, WHITE);
  display->drawLine(closeX + 2, closeY + 2, closeX + 6, closeY + 6, BLACK);
  display->drawLine(closeX + 2, closeY + 6, closeX + 6, closeY + 2, BLACK);
  
}

void drawButton(Display * display, const char * str, int x, int y, bool active) {
  
  int16_t len = strlen_P(str);
  
  int width = len * 6 + 1;
  int height = 10;
  
  display->drawFastHLine(x + 1, y, width - 1, BLACK);
  display->drawFastHLine(x + 1, y + height, width - 1, BLACK);
  display->drawFastHLine(x + 2, y + height + 1, width - 1, BLACK);

  display->drawFastVLine(x, y + 1, height - 1, BLACK);
  display->drawFastVLine(x + width, y + 1, height, BLACK);
  display->drawFastVLine(x + width + 1, y + 2, height - 1, BLACK);
  
  display->fillRect(x + 1, y + 1, width - 2, height - 2, active ? BLACK : WHITE);
  
  unsigned char byte;
  for(int16_t k = 0; k < len; k++) {
    byte = pgm_read_byte_near(str + k);
    display->drawChar(x + 1 + k * 6, y + 2, byte, active ? WHITE : BLACK, active ? BLACK : WHITE, 1);
  }
  
}