#include "game.h"
#include "io.h"

#include "scenes/logos.h"
#include "scenes/splash.h"
#include "scenes/tetris.h"
#include "scenes/enterscore.h"

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
      Scene * oldScene = currentScene;
      if(currentScene->switchToScene == LOGOS) {
        currentScene = new LogosScene();
      } else if(currentScene->switchToScene == SPLASH) {
        currentScene = new SplashScene();
      } else if(currentScene->switchToScene == TETRIS) {
        currentScene = new TetrisScene();
      } else if(currentScene->switchToScene == ENTER_HIGH_SCORE) {
        currentScene = new EnterScoreScene();
      }
      currentScene->init();
      delete oldScene;
    }
  }
}

void Game::setScene(Scene * scene) {
  currentScene = scene;
  currentScene->init();
}