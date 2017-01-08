#include "gameover.h"
#include "strings.h"
#include "io.h"

#define CURSOR_FLASH_DURATION							700

const unsigned char skullIcon [] PROGMEM = {
	// 'skull'
	0x38, 0x00, 0x38, 0x00, 0x28, 0x00, 0x28, 0x00, 0xc8, 0x00, 0x26, 0x00, 0x85, 0xff, 0x42, 0x00, 
	0xe6, 0x00, 0xce, 0x00, 0x1c, 0x00, 0x70, 0x00, 0x08, 0x00, 0x20, 0x00, 0x10, 0x00, 0x10, 0x00, 
	0x10, 0x00, 0x10, 0x00, 0x11, 0x83, 0x10, 0x00, 0x13, 0x46, 0x90, 0x00, 0x13, 0xc7, 0x90, 0x00, 
	0x13, 0xc7, 0x90, 0x00, 0x11, 0x93, 0x10, 0x00, 0x12, 0x38, 0x90, 0x00, 0x08, 0x38, 0x20, 0x00, 
	0x0e, 0x00, 0xe0, 0x00, 0x13, 0x01, 0x90, 0x00, 0xe2, 0xaa, 0x8e, 0x00, 0x84, 0xaa, 0x42, 0x00, 
	0xc8, 0xfe, 0x26, 0x00, 0x28, 0x00, 0x28, 0x00, 0x38, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

void GameOverScene::init() {
	scoreEntry.score = getPendingScore();
	shouldCrash = !isHighScore(scoreEntry.score);
	animStartTime = millis();
}

void GameOverScene::tick() {
	
	if(animProgress < 1) {
		animProgress = min(1, (float)(millis() - animStartTime) / animDuration);
		if(animProgress < GAMEOVER_STEP_1) {
      // Slide the screen shut
			if(nextStep < 0) {
				nextStep = 0;
			}
		} else if(animProgress < GAMEOVER_STEP_2) {
      // Show progress bar
			if(nextStep < 1) {
				nextStep = 1;
			}
		} else if(animProgress < GAMEOVER_STEP_3) {
      // Show error message
			if(nextStep < 2) {
				nextStep = 2;
			}
		}
	}
	
	if(currentStep == 3) {
		// Text entry
		bool didMoveCursor = false;
		if(isButtonDown(BUTTON_L, 300)) {
			if(okButtonHighlighted) {
				okButtonHighlighted = false;
				buttonNeedsRedraw = true;
			} else if(characterIndex > 0) {
				characterIndex--;
			}
			didMoveCursor = true;
		} else if(isButtonDown(BUTTON_R, 300)) {
			if(characterIndex >= 5) {
				okButtonHighlighted = true;
				buttonNeedsRedraw = true;
			} else {
				characterIndex++;
			}
			didMoveCursor = true;
		} else if(isButtonDown(BUTTON_A, 130)) {
			if(okButtonHighlighted) {
				// Clicking A when OK button is highlighted
				saveScore();
			} else {
				// Down
				char chr = scoreEntry.name[characterIndex];
				if(chr == 'Z') {
					scoreEntry.name[characterIndex] = ' ';
				} else if(chr == ' ') {
					scoreEntry.name[characterIndex] = 'A';
				} else {
					scoreEntry.name[characterIndex] = chr + 1;
				}
				didMoveCursor = true;
			}
		} else if(isButtonDown(BUTTON_B, 130)) {
			if(okButtonHighlighted) {
				// Clicking B when OK button is highlighted
				saveScore();
			} else {
				// Up
				char chr = scoreEntry.name[characterIndex];
				if(chr == ' ') {
					scoreEntry.name[characterIndex] = 'Z';
				} else if(chr == 'A') {
					scoreEntry.name[characterIndex] = ' ';
				} else {
					scoreEntry.name[characterIndex] = chr - 1;
				}
				didMoveCursor = true;
			}
		}
		if(didMoveCursor) {
			nextCursorFlash = millis() + CURSOR_FLASH_DURATION;
			cursorVisible = true;
			nameNeedsRedraw = true;
		}
	}
	
}

void GameOverScene::render(Display * display) {
	
	bool didDraw = false;
	
	// if(needsWipe) {
	// 	needsRedraw = true;
	// 	needsWipe = true;
	// 	didDraw = true;
	// 	display->fillScreen(WHITE);
	// }
  
  // display->fillRect(5, 60, 86 * (animProgress / 1.0), 30, BLACK);
  // display->refresh();
	
	if(nextStep == 0) {
		
		// Progress bar geom
		int pw = 70;
		int ph = 8;
		int px = 12;
		int py = 54;
		
		// Draw cool image
		if(currentStep != 0) {
			currentStep = 0;
			
			// Draw dialog box with progress bar
			display->fillScreen(WHITE);
			drawDialog(display, STR_PLEASE_WAIT, 6, 12, 82, 70);
			
			drawProgString(display, 12, 30, STR_EMPTYING, BLACK, WHITE);
			drawProgString(display, 12, 41, STR_TRASH, BLACK, WHITE);
			
			// Empty progress bar
			display->drawFastHLine(px + 1, py, pw - 1, BLACK);
			display->drawFastHLine(px + 1, py + ph, pw - 1, BLACK);
			display->drawFastVLine(px, py + 1, ph - 1, BLACK);
			display->drawFastVLine(px + pw, py + 1, ph - 1, BLACK);
		}
		
		float prog = min(1, (animProgress / GAMEOVER_STEP_1) * 1.1);
		
		// Fill progress bar
		float barProg = (1.0 - pow(1.0 - prog, 2.0)) * (shouldCrash ? 0.7 : 1.0);
		display->fillRect(px + 2, py + 2, (pw - 3) * barProg, ph - 3, BLACK);
		
		// Draw score
		char buffer[10];
		itoa((float)scoreEntry.score * prog, buffer, 10);
		int scoreLength = 0;
		for(int k = 0; k < 9; k++) {
			if(buffer[k] == '\0') {
				scoreLength = k;
				break;
			}
		}
		display->setTextColor(BLACK, WHITE);
		display->setCursor(px, py + ph + 5);
		display->println(buffer);
		
		// int valLength = 0;
		drawProgString(display, px + 6 * (scoreLength), py + ph + 5, STR_DELETED_FILES, BLACK, WHITE);
		
		if(!isMuted()) tone(BUZZER_PIN, 400 + barProg * 1500);
    
    didDraw = true;
		
	} else if(nextStep == 1) {
		
		noTone(BUZZER_PIN);
		nextErrorTime = millis();
		
		// Just chill
		currentStep = 1;
		
	} else if(nextStep == 2) {
		
		if(currentStep != 2) {
			// tone(BUZZER_PIN, 400, 100);
			currentStep = 2;
		}
		
		// Show cool message
		if(shouldCrash) {
			// ERROR ERROR ERROR (score isn't good enough for a high score)
			if(millis() > nextErrorTime) {
				nextErrorTime = millis() + 100;
				int x = 2 + totalErrorsShown * 10;
				int y = 2 + totalErrorsShown * 10;
				didDraw = true;
				totalErrorsShown++;
				if(totalErrorsShown == 9) {
					if(!isMuted()) tone(BUZZER_PIN, 300, 600);
					display->fillScreen(BLACK);
					drawProgString(display, 21, 45, STR_GAME_OVER, WHITE, BLACK);display->refresh();
					delay(900);
					switchToScene = SPLASH;
					return;
				} else {
					if(!isMuted()) tone(BUZZER_PIN, 1000, 50);
					drawDialog(display, STR_ERROR_DIALOG, x, y, 50, 40);
					display->drawBitmap(x + 5, y + 15, skullIcon, 32, 32, BLACK);
				}
			}
		} else {
			// Plz enter ur name, cause you got a high score
			if(!isMuted()) tone(BUZZER_PIN, 1000, 300);
			nextStep = 3;
		}
		
	} else if(nextStep == 3) {
		
		int x = 2;
		int y = 20;
		int w = 88;
		int h = 62;
		
		int fX = x + 5;
		int fY = y + 17;
		
		if(currentStep != 3) {
			display->fillScreen(WHITE);
			currentStep = 3;
			drawDialog(display, STR_ENTER_NAME, x, y, w, h);
			display->drawRect(fX, fY, w - 9, 23, BLACK);
			didDraw = true;
			nameNeedsRedraw = true;
			nextCursorFlash = millis() + 700;
		}
		
		if(millis() >= nextCursorFlash) {
			cursorVisible = !cursorVisible;
			nameNeedsRedraw = true;
			nextCursorFlash = millis() + CURSOR_FLASH_DURATION;
		}
		
		if(nameNeedsRedraw) {
			for(int i = 0; i < 6; i++) {
				bool highlight = cursorVisible && characterIndex == i && okButtonHighlighted == false;
				display->drawChar(fX + 4 + i * 12, fY + 4, scoreEntry.name[i], highlight ? WHITE : BLACK, highlight ? BLACK : WHITE, 2);
			}
			didDraw = true;
		}
		
		if(buttonNeedsRedraw) {
			drawButton(display, STR_OK_BUTTON, x + 57, y + 45, okButtonHighlighted);
		}
		
	}
	
	if(didDraw) {
		display->refresh();
	}
}

void GameOverScene::saveScore() {
	addHighScore(scoreEntry);
	switchToScene = LEADERBOARD;
}

// Temporary store for current score
int pendingScore;
void setPendingScore(int val) {
  pendingScore = val;
}

int getPendingScore() {
  return pendingScore;
}