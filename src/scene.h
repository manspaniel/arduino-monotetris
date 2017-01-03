#ifndef SCENE_H
#define SCENE_H

#include "io.h"

enum SceneSwitchMode {
  NONE,
  LOGOS,
  SPLASH,
  TETRIS,
  ENTER_HIGH_SCORE
};

class Scene {
public:
  bool isFirstRender = true;
  bool goToSplashScreen = false;
  SceneSwitchMode switchToScene = NONE;
  // virtual ~Scene();
  virtual void init();
  virtual void tick();
  virtual void render(Display * display);
};

#endif