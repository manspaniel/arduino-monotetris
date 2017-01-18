#ifndef SPLASH_SCENE_H
#define SPLASH_SCENE_H

#include "../io.h"
#include "../scene.h"

class SplashScene : public Scene {
public:
  void init();
  void tick();
  void render(Display * display);
private:
  unsigned long startTime = 0;
  int stage = 0;
  unsigned long nextStageAt = 0;
  bool needsRedraw = false;
  
  // Intro anim
  float introProgress = 0;
  
  // Press any key
  bool pressAnyKeyState = false;
  unsigned long pressAnyKeyMillis = 0;
  
  // Menu selection
  int menuItem = 0;
  
  // Music
  unsigned long musicStartTime;
  unsigned long nextNoteAt;
  int musicIndex = -1;
  
  void tickMusic();
};

#endif