#include "main.h"

void setup(void) {

  display.begin();
  display.clearDisplay();
  
  game->start();

}

void loop(void) {
  
  game->tick();
  
}