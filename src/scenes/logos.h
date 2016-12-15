#ifndef LOGOS_SCENE_H
#define LOGOS_SCENE_H

#include "../io.h"
#include "../scene.h"

class LogosScene : public Scene {
public:
  void init();
  void tick();
  void render(Display * display);
private:
  bool needsRedraw = false;
  int stage = 0;
  int lastMillis = 0;
  unsigned int millisTillNextStage = 0;
  int millisPerStage = 2000;
};

#endif