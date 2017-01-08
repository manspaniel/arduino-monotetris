#ifndef GAMEOVER_SCENE_H
#define GAMEOVER_SCENE_H

#include "../io.h"
#include "../scene.h"
#include "../eep.h"

#define GAMEOVER_STEP_1         0.4       // Show progress bar
#define GAMEOVER_STEP_2         0.47      // Pause for a bit
#define GAMEOVER_STEP_3         1         // Show error OR, show 'Complete'

class GameOverScene : public Scene {
public:
  void init();
  void tick();
  void render(Display * display);
private:
  HighScore scoreEntry;
  bool shouldCrash = false;
  
  unsigned long animStartTime;
  unsigned long animDuration = 5000;
  float animProgress = 0;
  
  unsigned long nextErrorTime;
  char totalErrorsShown = 0;
  
  int nextStep = -1;
  int currentStep = -1;
  bool needsWipe = true;
  
  // Text entry
  unsigned long nextCursorFlash;
  bool cursorVisible = true;
  int characterIndex = 0;
  bool nameNeedsRedraw = false;
  bool okButtonHighlighted = false;
  bool buttonNeedsRedraw = true;
  
  void saveScore();
  
};


// Save pending score
void setPendingScore(int val);
int getPendingScore();

#endif