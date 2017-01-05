#include "game.h"
#include "io.h"
#include "fm.h"
#include "scenes/logos.h"
#include "scenes/splash.h"
#include "scenes/tetris.h"
#include "scenes/gameover.h"

Game::Game() {
  display = getMainDisplay();
}

void Game::start() {
  currentScene = new TetrisScene();
  currentScene->init();
  initButtons();
}

void Game::tick() {
  if(currentScene != NULL) {
    currentScene->tick();
    currentScene->render(display);
    currentScene->isFirstRender = false;
    if(currentScene->switchToScene != NONE) {
      SceneSwitchMode nextScene = currentScene->switchToScene;
      delete currentScene;
      currentScene = NULL;
      if(nextScene == SPLASH) {
        currentScene = new SplashScene();
      } else if(nextScene == TETRIS) {
        currentScene = new TetrisScene();
      } else if(nextScene == GAME_OVER) {
        currentScene = new GameOverScene();
      }
      currentScene->init();
    }
  }
  
  display->setCursor(0, 0);
  display->setTextColor(WHITE, BLACK);
  display->println(millis());
  display->refresh();
}

// void Game::setScene(Scene * scene) {
//   currentScene = scene;
//   currentScene->init();
// }