#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "io.h"
#include "scene.h"

class Game {
public:
  Scene * currentScene;
  Display * display;
  Game();
  void start();
  void tick();
  // void setScene(Scene * scene);
};

#endif