#ifndef LEADERBOARD_SCENE_H
#define LEADERBOARD_SCENE_H

#include "../io.h"
#include "../scene.h"

class LeaderBoardScene : public Scene {
public:
  void init();
  void tick();
  void render(Display * display);
private:
};


// Save pending score
void setHighlightIndex(int val);
int getHighlightIndex();

#endif