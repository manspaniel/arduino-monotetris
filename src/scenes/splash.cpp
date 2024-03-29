#include "splash.h"
#include "../fun_math.h"
#include "../io.h"
#include "../pitches.h"
#include "../eep.h"
#include "../strings.h"
#include "tetris.h"

// 'logoFull'
const unsigned char logoParts1 [] PROGMEM = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 
 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0xe0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x38, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x38, 0x00, 0x03, 0xff, 0xe0, 0xff, 0xe7, 0xff, 
 0x03, 0x80, 0x3c, 0x00, 0x07, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xc0, 0x07, 0xff, 
 0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x1f, 0xfc, 0x07, 0x00, 0x1f, 0x80, 0x7e, 0x01, 0xfc, 0x0e, 
 0x0f, 0xfe, 0x0e, 0x00, 0x0f, 0x80, 0x7c, 0x01, 0x80, 0x0e, 0x00, 0x0f, 0x0e, 0x00, 0x07, 0x80, 
 0x7c, 0x00, 0x00, 0x1f, 0x00, 0x07, 0x0e, 0x00, 0x07, 0x00, 0x78, 0x00, 0x00, 0x3f, 0x80, 0x03, 
 0x0e, 0x00, 0x07, 0x00, 0x78, 0x00, 0x00, 0x7f, 0xc0, 0x03, 0x0e, 0x06, 0x07, 0x00, 0x78, 0x00, 
 0x1f, 0xff, 0xfe, 0x07, 0x1c, 0x0e, 0x07, 0x00, 0x70, 0x00, 0x1f, 0xff, 0xfc, 0x0f, 0x1c, 0x0e, 
 0x07, 0x00, 0x70, 0x02, 0x0f, 0xff, 0xf0, 0x1e, 0x1c, 0x0e, 0x06, 0x00, 0x60, 0x06, 0x07, 0xff, 
 0xe0, 0x3c, 0x1c, 0x0c, 0x06, 0x00, 0x60, 0x07, 0x03, 0xff, 0xc0, 0xf8, 0x38, 0x00, 0x0e, 0x00, 
 0x60, 0x07, 0x83, 0xff, 0xc1, 0xf0, 0x38, 0x00, 0x0e, 0x00, 0x40, 0x07, 0xc3, 0xff, 0xc3, 0xc0, 
 0x38, 0x00, 0x1e, 0x00, 0x40, 0x0f, 0xc3, 0xff, 0x83, 0x80, 0x38, 0x00, 0x7c, 0x00, 0x00, 0x0f, 
 0xc3, 0xff, 0xc3, 0x80, 0x38, 0x00, 0x7c, 0x08, 0x04, 0x0f, 0x83, 0xff, 0x83, 0x80, 0x70, 0x20, 
 0x7c, 0x08, 0x04, 0x0f, 0x83, 0x87, 0x83, 0x80, 0x70, 0x20, 0x7c, 0x08, 0x04, 0x0f, 0x86, 0x01, 
 0x83, 0x80, 0x70, 0x20, 0x78, 0x18, 0x08, 0x1f, 0x80, 0x00, 0x03, 0x80, 0x70, 0x30, 0x38, 0x18, 
 0x08, 0x1f, 0x00, 0x00, 0x03, 0x80, 0x70, 0x30, 0x38, 0x18, 0x18, 0x1f, 0x00, 0x30, 0x03, 0x80, 
 0xe0, 0x70, 0x38, 0x18, 0x18, 0x1f, 0x00, 0xfc, 0x03, 0x80, 0xe0, 0x70, 0x18, 0x18, 0x10, 0x1f, 
 0x03, 0xfe, 0x03, 0x80, 0xe0, 0x78, 0x38, 0x38, 0x38, 0x3f, 0x0f, 0xff, 0x87, 0x80, 0x7f, 0xff, 
 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xfe, 0x03, 
 0xfe, 0x00, 0x1f, 0x87, 0xc7, 0xc7, 0xc7, 0xc0, 0xf0, 0x00, 0x78, 0x0
};
// 'logoRm'
const unsigned char logoParts2 [] PROGMEM = {
 0x03, 0xff, 0xe0, 0xff, 0xe7, 0xff, 0x00, 0x07, 0xff, 0xf9, 0xff, 0xff, 0xff, 0x80, 0x07, 0xff, 
 0xff, 0xff, 0xff, 0xff, 0xc0, 0x07, 0x00, 0x1f, 0x80, 0x7e, 0x01, 0xc0, 0x0e, 0x00, 0x0f, 0x80, 
 0x7c, 0x01, 0xc0, 0x0e, 0x00, 0x07, 0x80, 0x7c, 0x01, 0xc0, 0x0e, 0x00, 0x07, 0x00, 0x78, 0x03, 
 0x80, 0x0e, 0x00, 0x07, 0x00, 0x78, 0x03, 0x80, 0x0e, 0x06, 0x07, 0x00, 0x78, 0x03, 0x80, 0x1c, 
 0x0e, 0x07, 0x00, 0x70, 0x03, 0x80, 0x1c, 0x0e, 0x07, 0x00, 0x70, 0x03, 0x80, 0x1c, 0x0e, 0x06, 
 0x00, 0x60, 0x07, 0x00, 0x1c, 0x0c, 0x06, 0x00, 0x60, 0x07, 0x00, 0x38, 0x00, 0x0e, 0x00, 0x60, 
 0x07, 0x00, 0x38, 0x00, 0x0e, 0x00, 0x40, 0x07, 0x00, 0x38, 0x00, 0x1e, 0x00, 0x40, 0x0e, 0x00, 
 0x38, 0x00, 0x7c, 0x00, 0x00, 0x0e, 0x00, 0x38, 0x00, 0x7c, 0x08, 0x04, 0x0e, 0x00, 0x70, 0x20, 
 0x7c, 0x08, 0x04, 0x0e, 0x00, 0x70, 0x20, 0x7c, 0x08, 0x04, 0x0e, 0x00, 0x70, 0x20, 0x78, 0x18, 
 0x08, 0x1c, 0x00, 0x70, 0x30, 0x38, 0x18, 0x08, 0x1c, 0x00, 0x70, 0x30, 0x38, 0x18, 0x18, 0x1c, 
 0x00, 0xe0, 0x70, 0x38, 0x18, 0x18, 0x1c, 0x00, 0xe0, 0x70, 0x18, 0x18, 0x10, 0x1c, 0x00, 0xe0, 
 0x78, 0x38, 0x38, 0x38, 0x38, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7f, 0xff, 0xff, 
 0xff, 0xff, 0xf0, 0x00, 0x1f, 0x87, 0xc7, 0xc7, 0xc7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'logoStar'
const unsigned char logoParts3 [] PROGMEM = {
 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00, 
 0x00, 0xf1, 0xc0, 0x00, 0x00, 0x00, 0xe1, 0xc0, 0x00, 0x00, 0x01, 0xe0, 0xe0, 0x00, 0x00, 0x01, 
 0xc0, 0xe0, 0x00, 0x00, 0x03, 0x80, 0x70, 0x00, 0x00, 0x03, 0x80, 0x70, 0x00, 0x00, 0x07, 0x00, 
 0x78, 0x00, 0x00, 0xff, 0x00, 0x3f, 0x80, 0x1f, 0xfe, 0x0c, 0x3f, 0xf8, 0x3f, 0xf8, 0x1c, 0x1f, 
 0xfc, 0x7c, 0x00, 0x1c, 0x00, 0x1e, 0x70, 0x00, 0x3e, 0x00, 0x0e, 0x60, 0x00, 0x7f, 0x00, 0x06, 
 0xe0, 0x00, 0xff, 0x80, 0x06, 0x70, 0x3f, 0xff, 0xfc, 0x0e, 0x70, 0x3f, 0xff, 0xf8, 0x1e, 0x78, 
 0x1f, 0xff, 0xe0, 0x3c, 0x3c, 0x0f, 0xff, 0xc0, 0x78, 0x1e, 0x07, 0xff, 0x81, 0xf0, 0x0f, 0x07, 
 0xff, 0x83, 0xe0, 0x07, 0x87, 0xff, 0x87, 0x80, 0x03, 0x87, 0xff, 0x07, 0x00, 0x03, 0x87, 0xff, 
 0x87, 0x00, 0x07, 0x07, 0xff, 0x07, 0x00, 0x07, 0x07, 0x0f, 0x07, 0x00, 0x07, 0x0c, 0x03, 0x07, 
 0x00, 0x0f, 0x00, 0x00, 0x07, 0x00, 0x0e, 0x00, 0x00, 0x07, 0x00, 0x0e, 0x00, 0x60, 0x07, 0x00, 
 0x0e, 0x01, 0xf8, 0x07, 0x00, 0x0e, 0x07, 0xfc, 0x07, 0x00, 0x0e, 0x1f, 0xff, 0x0f, 0x00, 0x0f, 
 0xff, 0x0f, 0xfe, 0x00, 0x07, 0xfc, 0x07, 0xfc, 0x00, 0x01, 0xe0, 0x00, 0xf0, 0x0
};

const unsigned char menuArrow [] PROGMEM = {
	0x80, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define MUSIC_BIT_DURATION				130
#define MUSIC_TOTAL_NOTES		  		10
#define MUSIC_TOTAL_BITS		  		69

const uint16_t musicNotes [] PROGMEM = {
	NOTE_F5,		0,		1,
	NOTE_F5,		8,		1,
	NOTE_DS5,		11,		1,
	NOTE_F5,		14,		1,
  NOTE_F5,		23,		1,
  NOTE_DS5,		26,		1,
  NOTE_F5,		29,		1,
  NOTE_F5,		39,		1,
  NOTE_DS5,		42,		1,
  NOTE_CS5,		45,		16
};

#define LOGO_ROW_START 9
#define LOGO_ROW_HEIGHT 38

#define TOTAL_MENU_ITEMS 3

const float LOGO_LEFT_START = -60.0;
const float LOGO_LEFT_END = 9.0;

const float LOGO_RIGHT_START = 100.0;
const float LOGO_RIGHT_END = 50.0;

void SplashScene::init() {
  startTime = millis();
  musicStartTime = millis();
  nextNoteAt = millis();
}

void SplashScene::tick() {
  
  if(!isMuted()) {
    tickMusic();
  }
  
  if(stage == 0) {
    introProgress = ((float)millis() - (float)startTime) / 600;
    if(introProgress >= 1) {
      stage = 1;
      nextStageAt = millis() + 500;
    }
  } else if(nextStageAt != 0 && millis() >= nextStageAt) {
    stage++;
    needsRedraw = true;
    nextStageAt = 0;
    
    if(stage == 2) {
      nextStageAt = millis() + 500;
    } else if(stage == 3) {
      nextStageAt = millis() + 1300;
    }
  }
  
  if(stage == 4) {
    if(millis() > pressAnyKeyMillis) {
      pressAnyKeyMillis = millis() + 500;
      pressAnyKeyState = !pressAnyKeyState;
      needsRedraw = true;
    }
    if(isButtonDown(BUTTON_A) || isButtonDown(BUTTON_B)) {
      delay(500);
      stage = 5;
      needsRedraw = true;
    }
    
  } else if(stage == 5) {
    if(isButtonDown(BUTTON_L)) {
      // Serial.println("Left");
      menuItem--;
      needsRedraw = true;
      if(menuItem < 0) menuItem = TOTAL_MENU_ITEMS - 1;
    } else if(isButtonDown(BUTTON_R)) {
      // Serial.println("Right");
      menuItem++;
      needsRedraw = true;
      if(menuItem >= TOTAL_MENU_ITEMS) menuItem = 0;
    } else if(isButtonDown(BUTTON_A) || isButtonDown(BUTTON_B)) {
      if(menuItem == 0) {
        // Start a new game!
        switchToScene = TETRIS;
      } else if(menuItem == 1) {
        switchToScene = LEADERBOARD;
      } else if(menuItem == 2) {
        setMuted(!isMuted());
        needsRedraw = true;
      }
    }
  }
  
}

void SplashScene::tickMusic() {
  
  if(millis() >= nextNoteAt) {
    musicIndex++;
    if(musicIndex < MUSIC_TOTAL_NOTES) {
      tone(BUZZER_PIN, pgm_read_word_near(musicNotes + musicIndex * 3), pgm_read_word_near(musicNotes + musicIndex * 3 + 2) * MUSIC_BIT_DURATION);
    }
    
    if(musicIndex + 1 < MUSIC_TOTAL_NOTES) {
      nextNoteAt = musicStartTime + pgm_read_word_near(musicNotes + (musicIndex + 1) * 3 + 1) * MUSIC_BIT_DURATION;
    }
    
  }
  
  if(millis() > (unsigned long)(musicStartTime + MUSIC_BIT_DURATION * MUSIC_TOTAL_BITS)) {
    musicIndex = -1;
    musicStartTime = millis();
    nextNoteAt = millis();
  }
  
  // int currentMusicIndex = (millis() - startTime) / (float)MUSIC_BIT_DURATION;
  // 
  // if(currentMusicIndex > musicNoteIndex) {
  //   musicNoteIndex = currentMusicIndex;
  //   tone(BUZZER_PIN, musicNotes[musicNoteIndex * 3], musicNotes[musicNoteIndex * 3])
  // }
  // 
}

void SplashScene::render(Display * display) {
  if(isFirstRender) {
    display->fillScreen(1);
  }
  
  if(stage == 0 || stage == 1) {
    
    // Clear the logo area
    display->fillRect(0, LOGO_ROW_START, 96, LOGO_ROW_HEIGHT, WHITE);
    
    if(stage == 0 && introProgress < 1.0) {
      display->drawBitmap((int)funLerp(LOGO_LEFT_START, LOGO_LEFT_END, introProgress), 18, logoParts2, 55, 32, 0);
      display->drawBitmap((int)funLerp(LOGO_RIGHT_START, LOGO_RIGHT_END, introProgress), 9, logoParts3, 39, 38, 0);
    } else if(stage == 1) {
      display->drawBitmap(9, 9, logoParts1, 80, 38, 0);
    }
    
    display->refresh();
  } else if(stage == 2) {
    if(needsRedraw) {
      // Delete...
      display->setTextColor(BLACK);
      display->setCursor(30, 53);
      drawProgString(display, 30, 54, STR_DELETE, BLACK, WHITE);
      display->refresh();
    }
  } else if(stage == 3) {
    if(needsRedraw) {
      // ...Everything!
      display->setTextColor(BLACK);
      display->setCursor(17, 63);
      drawProgString(display, 17, 63, STR_EVERYTHING, BLACK, WHITE);
      display->refresh();
    }
  } else if(stage == 4) {
    if(needsRedraw) {
      int top = 78;
      display->setCursor(21, top);
      if(pressAnyKeyState) {
        display->setTextColor(BLACK);
        drawProgString(display, 21, top, STR_PRESS_AB, BLACK, WHITE);
      } else {
        display->fillRect(0, top, 96, 7, WHITE);
      }
      display->refresh();
    }
  } else if(stage == 5) {
    
    if(needsRedraw) {
      needsRedraw = false;
      
      // Clearing the area
      display->fillRect(0, 53, 96, 43, WHITE);
      
      // Display item names
      
      drawProgString(display, 34, 56, STR_PLAY, BLACK, WHITE);
      if(menuItem == 0) {
        display->drawBitmap(26, 57, menuArrow, 16, 16, BLACK);
      }
      
      drawProgString(display, 15, 68, STR_LEADERBOARD, BLACK, WHITE);
      if(menuItem == 1) {
        display->drawBitmap(7, 69, menuArrow, 16, 16, BLACK);
      }
      
      drawProgString(display, 35 - (isMuted() ? 6 : 0), 80, isMuted() ? STR_UNMUTE : STR_MUTE, BLACK, WHITE);
      if(menuItem == 2) {
        display->drawBitmap(27 - (isMuted() ? 6 : 0), 81, menuArrow, 16, 16, BLACK);
      }
      
      display->refresh();
      
      // delay(300);
    
    }
    
  }
  // display->fillRect(0, 0, 96, 7, WHITE);
  // display->setCursor(0, 0);
  // if(isButtonDown(BUTTON_A)) {
  //   display->println("DOWN!");
  // }
  // display->setCursor(50, 0);
  // if(isButtonDown(BUTTON_B)) {
  //   display->println("DOWN!");
  // }
  // display->fillRect(0, 96-8, 96, 7, WHITE);
  // display->setCursor(0, 96-8);
  // if(isButtonDown(BUTTON_L)) {
  //   display->println("DOWN!");
  // }
  // display->setCursor(50, 96-8);
  // if(isButtonDown(BUTTON_R)) {
  //   display->println("DOWN!");
  // }
  // display->refresh();
	// if(!needsRedraw) return;
	// needsRedraw = false;
	// display->fillScreen(0);
	// display->setTextColor(WHITE);
	// if(stage == 0) {
	//   display->drawBitmap(24, 13, ericsFace, 48, 65, 1);
	// } else if(stage == 1) {
	// 	// ED.
	//   display->drawBitmap(34, 39, edLogo, 32, 16, 1);
	// } else if(stage == 2) {
	// 	// ED. Presents...
	//   display->drawBitmap(34, 39, edLogo, 32, 16, 1);
	// 	display->setCursor(25,60);
	//   display->println("Presents");
	// 	millisTillNextStage = millis() + millisPerStage * 1.5;
	// }
	// display->refresh();
}