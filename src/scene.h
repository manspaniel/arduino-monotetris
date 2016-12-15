#ifndef SCENE_H
#define SCENE_H

#include "io.h"

class Scene {
public:
  bool isFirstRender = true;
  Scene * nextScene;
  virtual ~Scene();
  virtual void init();
  virtual void tick();
  virtual void render(Display * display);
};

#endif