#ifndef TETRIS_SCENE_H
#define TETRIS_SCENE_H

#include <avr/pgmspace.h>
#include "../io.h"
#include "../scene.h"

#define CHECK_BIT(var, pos) ((var) & (1<<(pos)))

enum GameState {
  PREPARING,
  PLAYING,
  SHOWING_EMOTE,
  _GAME_OVER
};

#define TOTAL_EMOTES 11

const char emote_1[] PROGMEM = {"Trm -rf ~/"};
const char emote_2[] PROGMEM = {"TDELETE *\nFROM wp_posts"};
const char emote_3[] PROGMEM = {"DDelete? Y/N\n> \t\t\t\t\t\t\t\t\t\tY"};
const char emote_4[] PROGMEM = {"DThis cannot\nbe undone"};
const char emote_5[] PROGMEM = {"DSubscribers\nerased"};
const char emote_6[] PROGMEM = {"Twp_delete_post()"};
const char emote_7[] PROGMEM = {"DFormatting\npartition..."};
const char emote_8[] PROGMEM = {"DMake a backup\nfirst?\n> \t\t\t\t\t\t\t\t\t\tN"};
const char emote_9[] PROGMEM = {"D1 post\nmoved to\nthe Trash"};
const char emote_10[] PROGMEM = {"DNotes not\nfound"};
const char emote_11[] PROGMEM = {"DAccount\ndeleted"};

const char* const emoteList[TOTAL_EMOTES] PROGMEM = {
  emote_1,
  emote_2,
  emote_3,
  emote_4,
  emote_5,
  emote_6,
  emote_7,
  emote_8,
  emote_9,
  emote_10,
  emote_11
};

static const bool tetrisShapes[] PROGMEM = {
  0,1,1,0,
  0,1,1,0,
  0,0,0,0,
  
  0,0,1,0,
  0,1,1,0,
  0,1,0,0,
  
  0,1,0,0,
  0,1,1,0,
  0,0,1,0,
  
  0,1,1,0,
  0,0,1,0,
  0,0,1,0,
  
  0,1,1,0,
  0,1,0,0,
  0,1,0,0,
  
  0,0,1,0,
  0,1,1,0,
  0,0,1,0,
  
  0,0,0,0,
  1,1,1,1,
  0,0,0,0
};

class TetrisScene : public Scene {
public:
  void init();
  void tick();
  void render(Display * display);
private:
  
  // Config
  int CELLS_WIDE = 10;
  int CELLS_HIGH = 17;
  long rowsToDestroy;      // bitfield
  unsigned char canvas[22];
  
  // Game state
  GameState gameState;
  int currentLevel = 1;
  int score = 0;
  int linesDestroyed = 0;
  
  int emoteToShow = 0;
  int emoteType;
  bool emoteBGDrawn = false;
  unsigned long emoteStartTime;
  unsigned long emoteEndTime;
  
  int rowFlashesLeft = 0;
  unsigned long nextRowFlash = 0;
  bool rowFlashNeedsRendering = false;
  bool rowsNeedDeleting = false;
  
  float currentSpeed;
  unsigned long gameStartTime;
  unsigned long nextDropTime;
  
  int prepareStep = 0;
  
  // Current shape
  int posX = 0;
  int posY = 0;
  char rotation = 0;
  char nextShape;
  char currentShape;
  bool hasCurrentShape = false;
  bool hasNextShape = false;
  
  // Draw updates..
  bool displayNeedsWipe = true;
  bool backgroundNeedsDrawing = true;
  bool levelNeedsDrawing = true;
  bool scoreNeedsDrawing = true;
  bool canvasNeedsDrawing = true;
  bool nextShapeNeedsDrawing = true;
  
  // Game over state
  // unsigned long gameOverStarted = 0;
  // float gameOverAnimDuration = 4000;
  // float gameOverAnimProgress = 0;
  // int gameOverStep = 0;
  // int completedGameOverStep = 0;
  
  // UI drawing
  void drawBackground(Display * display);
  void drawLevel(Display * display);
  void drawScore(Display * display);
  void drawNextShape(Display * display);
  void drawCanvas(Display * display);
  void drawEmote(Display * display);
  
  // Draw utils
  void drawFrame(Display * display, int x, int y, int width, int height);
  void drawShape(Display *display, char shape, int offsetX, int offsetY, int rotation);
  
  // Shape
  bool isValidPlacement(char shape, int x, int y, int rotation);
  bool getShapePixel(char shape, int x, int y, int rotation);
  bool probeCanvas(int x, int y);
  void applyShape(char shape, int x, int y, int rotation);
  
  // Gameplay functions
  void triggerGameOver();           // End the game
  void checkForFilledRows();
  void shiftCanvasDown(int from);
  void adjustLevel();
  
  // Tickers..
  void tickGame();
  
  void enterGameOver();
  
};

// const unsigned char fuckImage [] PROGMEM = {
// 	// 'fuck'
// 	0x0f, 0xfe, 0xfc, 0x7e, 0x0f, 0xe0, 0x7c, 0x7e, 0x1f, 0xfe, 0xf8, 0x7c, 0x1f, 0xf0, 0x7c, 0xfe, 
// 	0x1f, 0xfc, 0xf8, 0x7c, 0x3f, 0xf8, 0x7c, 0xfc, 0x1f, 0xfc, 0xf8, 0x7c, 0x7f, 0xf8, 0x7d, 0xf8, 
// 	0x1f, 0xfd, 0xf8, 0xfc, 0xff, 0xfc, 0xfd, 0xf8, 0x3f, 0x01, 0xf0, 0xf8, 0xf8, 0xfc, 0xfb, 0xf0, 
// 	0x3e, 0x01, 0xf0, 0xf9, 0xf8, 0x7c, 0xff, 0xe0, 0x3e, 0x01, 0xf0, 0xf9, 0xf0, 0xfc, 0xff, 0xe0, 
// 	0x3f, 0xf9, 0xf0, 0xf9, 0xf0, 0x00, 0xff, 0xc0, 0x3f, 0xf3, 0xf1, 0xf9, 0xf0, 0x01, 0xff, 0x80, 
// 	0x7f, 0xf3, 0xe1, 0xf3, 0xf0, 0x01, 0xff, 0x80, 0x7f, 0xf3, 0xe1, 0xf3, 0xe0, 0xf9, 0xff, 0x80, 
// 	0x7f, 0xe3, 0xe1, 0xf3, 0xe1, 0xf9, 0xff, 0xc0, 0x7c, 0x03, 0xe3, 0xf3, 0xe1, 0xf3, 0xf7, 0xc0, 
// 	0x7c, 0x03, 0xe3, 0xe3, 0xf3, 0xf3, 0xe7, 0xc0, 0xf8, 0x03, 0xff, 0xe3, 0xff, 0xe3, 0xe7, 0xc0, 
// 	0xf8, 0x03, 0xff, 0xc1, 0xff, 0xe3, 0xe7, 0xe0, 0xf8, 0x03, 0xff, 0xc1, 0xff, 0xc3, 0xe7, 0xe0, 
// 	0xf8, 0x01, 0xff, 0x00, 0xff, 0x87, 0xe7, 0xe0, 0xf0, 0x00, 0x7c, 0x00, 0x3c, 0x03, 0xc3, 0xe0, 
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// };

#endif