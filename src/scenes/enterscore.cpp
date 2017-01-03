#include "enterscore.h"
#include "strings.h"
#include "io.h"

void EnterScoreScene::init() {
	highScore.score = getPendingScore();
	
	animStartTime = millis();
}

void EnterScoreScene::tick() {
	
	if(animProgress < 1) {
		animProgress = min(1, (float)(millis() - animStartTime) / animDuration);
		if(animProgress < HIGH_SCORE_IMG_ENDS && nextStep != 0) {
			nextStep = 0;
			needsRedraw = true;
		} else if(animProgress < SCORE_DISPLAY_ENDS && nextStep != 1) {
			nextStep = 1;
			needsRedraw = true;
		} else if(animProgress < COOL_MESSAGE_ENDS && nextStep != 2) {
			nextStep = 2;
			needsRedraw = true;
		}
	}
	
}

void EnterScoreScene::render(Display * display) {
	
	bool didDraw = false;
	
	if(needsWipe) {
		needsRedraw = true;
		needsWipe = true;
		didDraw = true;
		display->fillScreen(WHITE);
	}
	
	if(needsRedraw) {
		
		if(nextStep == 0) {
			
			// Draw cool image
			currentStep = 0;
			
			display->fillRect(5, 5, 86, 30, BLACK);
			display->drawRect(5, 5, 86, 30 * animProgress / HIGH_SCORE_IMG_ENDS, WHITE);
			
		} else if(nextStep == 1) {
			
			// Show score!
			if(currentStep != 1) {
				currentStep = 1;
				char buffer[10];
				itoa(highScore.score, buffer, 10);
				int scoreLength = 0;
				for(int k = 0; k < 9; k++) {
					if(buffer[k] == '\0') {
						scoreLength = k;
						break;
					}
				}
				display->setTextColor(WHITE, BLACK);
				display->setCursor(48 - scoreLength * 3, 70);
				display->println(buffer);
			}
			
		} else if(nextStep == 2) {
			
			// Show cool message
			if(currentStep != 2) {
				currentStep = 2;
				display->setTextColor(WHITE, BLACK);
				display->setCursor(25, 80);
				display->println("Files Deleted");
			}
			
		}
		
	}
	
	if(didDraw) {
		display->refresh();
	}
	
	// display->fillScreen(WHITE);
	// char buffer[10];
	// itoa(highScore.score, buffer, 10);
	// int scoreLength = 0;
	// for(int k = 0; k < 9; k++) {
	// 	if(buffer[k] == '\0') {
	// 		scoreLength = k;
	// 		break;
	// 	}
	// }
	// display->setTextColor(WHITE, BLACK);
	// display->setCursor(48 - scoreLength * 3, 70);
	// display->println(buffer);
	// display->refresh();
}

// Temporary store for current score
static int currentlyPendingScore;
void setPendingScore(int val) {
  currentlyPendingScore = val;
}

int getPendingScore() {
  return currentlyPendingScore;
}