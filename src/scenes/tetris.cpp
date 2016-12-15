#include "tetris.h"
#include "../io.h"
#include "../eep.h"

void TetrisScene::init() {
  
  gameStartTime = millis() + 4000;
  gameState = PREPARING;
  
}

void TetrisScene::tick() {
  
  if(gameState == PREPARING) {
    if(millis() > gameStartTime) {
      gameState = PLAYING;
    }
  } else if(gameState == PLAYING) {
    if(rowFlashesLeft > 0) {
      if(millis() > nextRowFlash) {
        rowFlashesLeft--;
        nextRowFlash = millis() + 200;
        rowFlashNeedsRendering = true;
      }
    } else {
      tickGame();
    }
  } else if(gameState == GAME_OVER) {
    tickGameOver();
  }
  
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
    nextDropTime = millis() + 400;
    
    if(!hasNextShape) {
      // nextShape = random(0, TOTAL_SHAPES);
      nextShape = 6;
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
        gameState = GAME_OVER;
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
        scoreNeedsDrawing = true;
        checkForFilledRows();
      }
      
      canvasNeedsDrawing = true;
    }
    
    // Pressing/holding A just shortens the length of time until the next drop
    if(isButtonDown(BUTTON_A)) {
      nextDropTime = min(nextDropTime, millis() + 60);
    }
  }
  
  // Rotate at any time
  if(isButtonDown(BUTTON_B)) {
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

void TetrisScene::tickGameOver() {
  if(gameOverStarted == 0) {
    gameOverStarted = millis();
  } else if(gameOverAnimProgress < 1) {
    gameOverAnimProgress = (float)(millis() - gameOverStarted) / gameOverAnimDuration;
  }
}

void TetrisScene::render(Display * display) {
  bool displayUpdated = false;
  if(displayNeedsWipe) {
    display->fillScreen(WHITE);
    displayUpdated = true;
    displayNeedsWipe = false;
  }
  if(backgroundNeedsDrawing) {
    drawBackground(display);
    displayUpdated = true;
    backgroundNeedsDrawing = false;
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
  
  // Draw game over screen
  if(gameState == GAME_OVER) {
    if(drawGameOver(display)) {
      displayUpdated = true;
    }
  }
  
  if(displayUpdated) {
    display->refresh();
  }
}

bool TetrisScene::drawGameOver(Display * display) {
  
  float progress = gameOverAnimProgress;
  
  bool didDraw = false;
  
  if(gameOverStep == 0) {
    if(progress >= 0.3) {
      gameOverStep = 1;
      progress = 0.3;
    }
    int height = (progress / 0.3) * (96.0 / 2.0);
    display->fillRect(0, 0, 96, height, BLACK);
    display->fillRect(0, 96-height, 96, height, BLACK);
    didDraw = true;
  } else if(gameOverStep == 1) {
    if(completedGameOverStep != 1) {
      display->drawBitmap(16, 29, fuckImage, 63, 20, WHITE);
      completedGameOverStep = 1;
      didDraw = true;
    }
    if(progress >= 0.6) {
      gameOverStep = 2;
    }
  } else if(gameOverStep == 2) {
    if(completedGameOverStep != 2) {
      display->setTextColor(WHITE);
      display->setCursor(25, 56);
      display->println("Only got");
      completedGameOverStep = 2;
      didDraw = true;
    }
    if(progress >= 0.85) {
      gameOverStep = 3;
    }
  } else if(gameOverStep == 3) {
    if(completedGameOverStep != 3) {
      char buffer[10];
      itoa(score, buffer, 10);
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
      completedGameOverStep = 3;
      didDraw = true;
    }
  }
  
  return didDraw;
  
}

void TetrisScene::drawBackground(Display * display) {
  // Serial.println("Drawing bG");
  
  // Main game area rect
  drawFrame(display, 3, 4, 53, 88);
  
  // LVL / Score / High Score / Next
  display->setTextColor(BLACK);
  display->setCursor(59, 5);
  display->println("Lvl 99");
  
  display->setCursor(59, 16);
  display->println("Score:");
  
  display->setCursor(59, 36);
  display->println("High:");
  display->setCursor(59, 45);
  HighScore highestScore = getHighScore(0);
  display->println(highestScore.score);
  
  display->setCursor(59, 56);
  display->println("Next:");
  
  drawFrame(display, 59, 66, 34, 26);
  
}

void TetrisScene::drawFrame(Display * display, int x, int y, int width, int height) {
  
  display->drawRect(x, y, width, height, BLACK);
  display->drawFastHLine(x+1, y+height, width, BLACK);
  display->drawFastVLine(x+width, y+1, height, BLACK);
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
  if(y > CELLS_HIGH - 1) return true;
  if(x < 0 || x >= CELLS_WIDE) return true;
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
    score += pow(lineCount, 1.5);
    scoreNeedsDrawing = true;
    int emote = 0;
    rowFlashesLeft = 11;
    nextRowFlash = 0;
    if(linesDestroyed > 150) {
      emote = 11;
    } else if(linesDestroyed > 100) {
      emote = 10;
    } else if(linesDestroyed > 80) {
      emote = 9;
    } else if(linesDestroyed > 50) {
      emote = 8;
    } else if(linesDestroyed > 30) {
      emote = 7;
    } else if(linesDestroyed > 20) {
      emote = 6;
    } else if(linesDestroyed > 15) {
      emote = 5;
    } else if(linesDestroyed > 10) {
      emote = 4;
    } else if(linesDestroyed > 6) {
      emote = 3;
    } else if(linesDestroyed > 3) {
      emote = 2;
    } else if(linesDestroyed > 1) {
      emote = 1;
    }
    if(emote > lastEmoteShown) {
      aboutToShowEmote = emote;
    }
  }
  
}

void TetrisScene::triggerGameOver() {
  
}