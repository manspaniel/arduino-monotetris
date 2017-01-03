#ifndef SCORE_SCENE_H
#define SCORE_SCENE_H

#include "../io.h"
#include "../scene.h"
#include "../eep.h"

#define HIGH_SCORE_IMG_ENDS       0.25
#define SCORE_DISPLAY_ENDS        0.5
#define COOL_MESSAGE_ENDS         0.9

class EnterScoreScene : public Scene {
public:
  HighScore highScore;
  
  void init();
  void tick();
  void render(Display * display);
private:
  unsigned long animStartTime;
  unsigned long animDuration = 5000;
  float animProgress = 0;
  
  int nextStep = 0;
  int currentStep = -1;
  bool needsWipe = true;
  bool needsRedraw = true;
};


// Save pending score
void setPendingScore(int val);
int getPendingScore();

#endif