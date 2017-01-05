#include "leaderboard.h"
#include "strings.h"
#include "io.h"
// #include "drawing.h"

void LeaderBoardScene::init() {
	
}

void LeaderBoardScene::tick() {

}

void LeaderBoardScene::render(Display * display) {
	
}

// Temporary store for current score
static int indexToHighlight = -1;
void setHighlightIndex(int val) {
  indexToHighlight = val;
}

int getHighlightIndex() {
  return indexToHighlight;
}