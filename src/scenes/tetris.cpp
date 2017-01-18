#include "tetris.h"
#include "../io.h"
// #include "../drawing.h"
#include "../eep.h"
#include "../strings.h"
#include "gameover.h"

#include "pitches.h"

#define ROW_FLASH_DURATION   50
#define TOTAL_SHAPES         7
#define LEVEL_STEP           150
#define EMOTE_DURATION       1200

void TetrisScene::init() {
  
  gameStartTime = millis() + 3000;
  gameState = PREPARING;
  
  randomSeed((int)millis());
  
}

void TetrisScene::tick() {
  
  if(gameState == PREPARING) {
    if(millis() > gameStartTime) {
      gameState = PLAYING;
      displayNeedsWipe = true;
      if(!isMuted()) tone(BUZZER_PIN, NOTE_C6, 800);
    }
  } else if(gameState == PLAYING) {
    if(rowFlashesLeft > 0) {
      if(!isMuted()) tone(BUZZER_PIN, random(50, 4500));
      if(millis() > nextRowFlash) {
        rowFlashesLeft--;
        nextRowFlash = millis() + ROW_FLASH_DURATION;
        rowFlashNeedsRendering = true;
        if(rowFlashesLeft == 0) {
          if(!isMuted()) noTone(BUZZER_PIN);
          adjustLevel();
        }
      }
    } else {
      tickGame();
    }
  } else if(gameState == SHOWING_EMOTE) {
    if(millis() > emoteEndTime) {
      gameState = PLAYING;
      displayNeedsWipe = true;
      backgroundNeedsDrawing = true;
      levelNeedsDrawing = true;
      scoreNeedsDrawing = true;
      canvasNeedsDrawing = true;
      nextShapeNeedsDrawing = true;
    }
  }
  
  // if(millis() > gameStartTime + 1000) {
    // setPendingScore(5731);
    // switchToScene = GAME_OVER;
  // }
  
}

void TetrisScene::tickGame() {
  
  if(rowsNeedDeleting) {
    // Some rows need deleting!
    for(long y = 0; y < CELLS_HIGH; y++) {
      if(rowsToDestroy & ((long)1 << y)) {
        shiftCanvasDown(y);
      }
    }
    rowsNeedDeleting = false;
  }
  
  if(millis() > nextDropTime) {
    nextDropTime = millis() + 450 - max(0.0f, (currentLevel / 20.0f) * 440.0f);
    
    if(!hasNextShape) {
      nextShape = random(0, TOTAL_SHAPES);
      hasNextShape = true;
      nextShapeNeedsDrawing = true;
    }
    
    if(!hasCurrentShape) {
      posX = 3;
      posY = 0;
      if(isValidPlacement(nextShape, posX, posY, rotation)) {
        currentShape = nextShape;
        hasCurrentShape = true;
      } else {
        enterGameOver();
        return;
      }
      hasNextShape = false;
      nextShapeNeedsDrawing = true;
    } else {
      if(isValidPlacement(currentShape, posX, posY + 1, rotation)) {
        posY += 1;
      } else {
        hasCurrentShape = false;
        applyShape(currentShape, posX, posY, rotation);
        score += 1;
        adjustLevel();
        scoreNeedsDrawing = true;
        checkForFilledRows();
      }
      
      canvasNeedsDrawing = true;
    }
    
    // Pressing/holding A just shortens the length of time until the next drop
    if(isButtonDown(BUTTON_A)) {
      nextDropTime = min(nextDropTime, millis() + 45);
    }
  }
  
  // Rotate at any time
  if(isButtonDown(BUTTON_B, 400)) {
    // Rotate, if possible
    canvasNeedsDrawing = true;
    char nextRotation = rotation == 3 ? 0 : rotation + 1;
    if(isValidPlacement(currentShape, posX, posY, nextRotation)) {
      rotation = nextRotation;
    }
    nextShapeNeedsDrawing = true;
  } else if(isButtonDown(BUTTON_L)) {
    if(isValidPlacement(currentShape, posX - 1, posY, rotation)) {
      posX -= 1;
      canvasNeedsDrawing = true;
    }
  } else if(isButtonDown(BUTTON_R)) {
    if(isValidPlacement(currentShape, posX + 1, posY, rotation)) {
      posX += 1;
      canvasNeedsDrawing = true;
    }
  }
}

void TetrisScene::adjustLevel() {
  int levelShouldBe = floor((float)score/LEVEL_STEP) + 1;
  if(currentLevel != levelShouldBe) {
    gameState = SHOWING_EMOTE;
    emoteToShow = (emoteToShow + 1) % (TOTAL_EMOTES);
    emoteStartTime = millis();
    emoteEndTime = millis() + EMOTE_DURATION;
    emoteBGDrawn = false;
    currentLevel = levelShouldBe;
  }
}

void TetrisScene::enterGameOver() {
  setPendingScore(score);
  switchToScene = GAME_OVER;
}

void TetrisScene::render(Display * display) {
  bool displayUpdated = false;
  if(displayNeedsWipe) {
    display->fillScreen(WHITE);
    displayUpdated = true;
    displayNeedsWipe = false;
  }
  if(gameState == PLAYING) {
    if(backgroundNeedsDrawing) {
      drawBackground(display);
      displayUpdated = true;
      backgroundNeedsDrawing = false;
    }
    if(levelNeedsDrawing) {
      drawLevel(display);
      displayUpdated = true;
      levelNeedsDrawing = false;
    }
    if(scoreNeedsDrawing) {
      drawScore(display);
      displayUpdated = true;
      scoreNeedsDrawing = false;
    }
    if(nextShapeNeedsDrawing) {
      drawNextShape(display);
      displayUpdated = true;
      nextShapeNeedsDrawing = false;
    }
    if(canvasNeedsDrawing) {
      drawCanvas(display);
      displayUpdated = true;
      canvasNeedsDrawing = false;
    }
  }
  if(gameState == PREPARING) {
    unsigned long timeLeft = (gameStartTime - millis());
    if(timeLeft < (unsigned long)1000 && prepareStep < 3) {
      prepareStep = 3;
      display->fillScreen(WHITE);
      if(!isMuted()) tone(BUZZER_PIN, NOTE_C5, 150);
      drawProgString(display, 40, 42, STR_GO, BLACK, WHITE);
      displayUpdated = true;
    } else if(timeLeft < (unsigned long)2000 && prepareStep < 2) {
      prepareStep = 2;
      display->fillScreen(WHITE);
      if(!isMuted()) tone(BUZZER_PIN, NOTE_C5, 150);
      drawProgString(display, 38, 42, STR_SET, BLACK, WHITE);
      displayUpdated = true;
    } else if(prepareStep < 1) {
      prepareStep = 1;
      display->fillScreen(WHITE);
      if(!isMuted()) tone(BUZZER_PIN, NOTE_C5, 150);
      drawProgString(display, 29, 42, STR_READY, BLACK, WHITE);
      displayUpdated = true;
    }
  }
  
  if(rowFlashNeedsRendering) {
    for(long y = 0; y <= CELLS_HIGH; y++) {
      if(rowsToDestroy & ((long)1 << y)) {
        if(rowFlashesLeft % 2) {
          display->fillRect(5, 6 + y * 5, 50, 4, WHITE);
        } else {
          for(int x = 0; x < CELLS_WIDE; x++) {
            display->drawRect(5 + x * 5, 6 + y * 5, 4, 4, BLACK);
          }
        }
      }
    }
    displayUpdated = true;
    rowFlashNeedsRendering = false;
  }
  
  if(gameState == SHOWING_EMOTE) {
    drawEmote(display);
    displayUpdated = true;
  }
  
  if(displayUpdated) {
    display->refresh();
  }
}

void TetrisScene::drawEmote(Display * display) {
  
  float progress = (float)(millis() - emoteStartTime) / EMOTE_DURATION;
  
  int totalRows = 1;
  int totalCols = 0;
  const char * text = (char*)pgm_read_word(&(emoteList[emoteToShow])) + 1;
  int len = strlen_P(text);
  
  unsigned char byte;
  int colsThisLine = 0;
  for(int16_t k = 0; k < len; k++) {
    byte = pgm_read_byte_near(text + k);
    if(byte == '\n') {
      colsThisLine = 0;
      totalRows++;
    } else if(byte == '\t') {
      continue;
    }
    colsThisLine++;
    totalCols = max(colsThisLine, totalCols);
  }
  
  int width = totalCols * 6 + 10;
  int height = totalRows * 10 + 17;
  int x = 48 - width/2;
  int y = 48 - height/2;
  int textX = x + 5;
  int textY = y + 16;
  
  if(!emoteBGDrawn) {
    drawDialog(display, STR_LVL_UP, x, y, width, height);
    emoteBGDrawn = true;
  }
  
  int col = 0;
  int row = 0;
  int limit = (progress * 1.2) * (float)len;
  for(int16_t k = 0; k < len; k++) {
    if(k > limit) {
      continue;
    }
    byte = pgm_read_byte_near(text + k);
    if(byte == '\n') {
      row++;
      col = 0;
      continue;
    } else if(byte == '\t') {
      continue;
    }
    if(k == limit) {
      if(!isMuted()) tone(BUZZER_PIN, NOTE_A2, 20);
    }
    display->drawChar(col * 6 + textX, row * 10 + textY, byte, BLACK, WHITE, 1);
    col++;
  }
  
}

void TetrisScene::drawBackground(Display * display) {
  
  // Main game area rect
  drawFrame(display, 3, 4, 53, 88);
  
  // LVL / Score / High Score / Next
  drawProgString(display, 59, 7, STR_LVL, BLACK, WHITE);
  drawProgString(display, 59, 16, STR_SCORE_COLON, BLACK, WHITE);
  drawProgString(display, 59, 36, STR_HIGH_COLON, BLACK, WHITE);
  drawProgString(display, 59, 56, STR_NEXT_COLON, BLACK, WHITE);
  
  display->setTextColor(BLACK);
  display->setCursor(59, 45);
  HighScore highestScore = getHighScore(0);
  display->println(highestScore.score);
  
  drawFrame(display, 59, 66, 34, 26);
  
}

void TetrisScene::drawFrame(Display * display, int x, int y, int width, int height) {
  
  display->drawRect(x, y, width, height, BLACK);
  display->drawFastHLine(x+1, y+height, width, BLACK);
  display->drawFastVLine(x+width, y+1, height, BLACK);
}

void TetrisScene::drawLevel(Display * display) {
  
  display->setTextColor(BLACK, WHITE);
  display->setCursor(83, 7);
  display->println(currentLevel);
  
}

void TetrisScene::drawScore(Display * display) {
  
  display->setTextColor(BLACK, WHITE);
  display->setCursor(59, 25);
  display->println(score);
  
}

void TetrisScene::drawCanvas(Display * display) {
  
  display->fillRect(5, 6, 49, 84, WHITE);
  
  for(int x = 0; x < CELLS_WIDE; x++) {
    for(int y = 0; y < CELLS_HIGH; y++) {
      // int index = y * CELLS_WIDE + x;
      // int byte = floor(index/8);
      if(probeCanvas(x, y)) {
        display->fillRect(5 + x * 5, 6 + y * 5, 4, 4, BLACK);
      }
    }
  }
  
  // Draw current shape
  if(hasCurrentShape) {
    drawShape(display, currentShape, 5 + posX * 5, 6 + posY * 5, rotation);
  }
  
}

void TetrisScene::drawNextShape(Display *display) {
  
  display->fillRect(60, 67, 32, 24, WHITE);
  
  if(hasNextShape) {
    drawShape(display, nextShape, 67, 72, 0);
  }
  
}

void TetrisScene::drawShape(Display *display, char shape, int offsetX, int offsetY, int rotation) {
  
  for(int x = 0; x < 4; x++) {
    for(int y = 0; y < 4; y++) {
      // int index = start + y * 4 + x;
      if(getShapePixel(shape, x, y, rotation)) {
        display->fillRect(offsetX + x * 5, offsetY + y * 5, 4, 4, BLACK);
      }
    }
  }
  
}

bool TetrisScene::getShapePixel(char shape, int x, int y, int rotation) {
  // Matrix isn't a square, so we ignore some out of bounds requests when rotating...
  if(y == 3 && (rotation == 0 || rotation == 2)) return false;
  if(x == 3 && (rotation == 1 || rotation == 3)) return false;
  
  int index = shape * 12;
  
  if(rotation == 0) {
    index += y * 4 + x;
  } else if(rotation == 1) {
    index += (2-x) * 4 + (y);//(2-x) * 4 + (3-y);
  } else if(rotation == 2) {
    index += (2-y) * 4 + (3-x);
  } else if(rotation == 3) {
    index += x * 4 + (3-y);
  }
  
  return pgm_read_byte_near(tetrisShapes + index) ? true : false;
}

// Gameplay utils
bool TetrisScene::isValidPlacement(char shape, int x, int y, int rotation) {
  for(int px = 0; px < 4; px++) {
    for(int py = 0; py < 4; py++) {
      if(getShapePixel(shape, px, py, rotation) && probeCanvas(x + px, y + py)) {
        return false;
      }
    }
  }
  return true;
}

bool TetrisScene::probeCanvas(int x, int y) {
  if(x < 0 || x >= CELLS_WIDE || y < 0 || y > CELLS_HIGH - 1) return true;
  int index = y * CELLS_WIDE + x;
  int byte = floor(index/8);
  return CHECK_BIT(canvas[byte], index % 8);
}

void TetrisScene::applyShape(char shape, int x, int y, int rotation) {
  for(int px = 0; px < 4; px++) {
    for(int py = 0; py < 4; py++) {
      if(getShapePixel(shape, px, py, rotation)) {
        // Color this square
        int index = (py+y) * CELLS_WIDE + (x+px);
        int byte = floor(index/8);
        canvas[byte] = canvas[byte] | (1 << (index % 8));
      }
    }
  }
}

void TetrisScene::shiftCanvasDown(int from) {
  
  for(int y = from; y > 1; y--) {
    for(int x = 0; x < CELLS_WIDE; x++) {
      int index = y * CELLS_WIDE + x;
      int byte = floor(index/8);
      if(probeCanvas(x, y - 1)) {
        canvas[byte] = canvas[byte] | (1 << (index % 8));
      } else {
        canvas[byte] = canvas[byte] & ~(1 << (index % 8));
      }
    }
  }
  
}

void TetrisScene::checkForFilledRows() {
  
  int lineCount = 0;
  
  rowsToDestroy = 0;
  for(int y = CELLS_HIGH - 1; y >= 0; y--) {
    bool lineIsFilled = true;
    for(int x = 0; x < CELLS_WIDE; x++) {
      if(!probeCanvas(x, y)) {
        lineIsFilled = false;
        break;
      }
    }
    if(lineIsFilled) {
      linesDestroyed++;
      lineCount++;
      rowsToDestroy = rowsToDestroy | ((long)1 << (long)y);
    }
  }
  
  // Add to score
  if(lineCount) {
    rowsNeedDeleting = true;
    score += pow(lineCount * 10, 1.5);
    scoreNeedsDrawing = true;
    rowFlashesLeft = 11;
    nextRowFlash = 0;
  }
  
}

void TetrisScene::triggerGameOver() {
  
}