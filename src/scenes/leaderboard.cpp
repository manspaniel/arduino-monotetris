#include "leaderboard.h"
#include "strings.h"
#include "io.h"
#include "eep.h"

#define DIALOG_WIDTH			80
#define DIALOG_HEIGHT			65
#define DIALOG_X     			7
#define DIALOG_Y     			14

void LeaderBoardScene::init() {
	buttonEnableTime = millis() + 800;
}

void LeaderBoardScene::tick() {
	if(isButtonDown(BUTTON_A) || isButtonDown(BUTTON_B)) {
		if(millis() > buttonEnableTime) {
			switchToScene = SPLASH;
		}
	}
}

void LeaderBoardScene::render(Display * display) {
	
	if(backgroundNeedsDrawing) {
		display->fillScreen(WHITE);
		drawDialog(display, STR_HIGH_SCORE_DIALOG, DIALOG_X, DIALOG_Y, DIALOG_WIDTH, DIALOG_HEIGHT);
	}
	
	for(int index = 0; index < EEP_TOTAL_HIGHSCORES; index++) {
		
		HighScore score = getHighScore(index);
		
		int y = DIALOG_Y + 17 + index * 9;
		
		if(score.score == 0) continue;
		
		// Name
		display->setTextColor(BLACK, WHITE);
		display->setCursor(5, y);
		for(int c = 0; c < 6; c++) {
			display->drawChar(DIALOG_X + 6 + 6 * c, y, score.name[c], BLACK, WHITE, 1);
		}
		
		// Score
		display->setCursor(57, y);
		display->println(score.score);
		
	}
	
	display->refresh();
	
}

// Temporary store for current score
static int indexToHighlight = -1;
void setHighlightIndex(int val) {
  indexToHighlight = val;
}

int getHighlightIndex() {
  return indexToHighlight;
}