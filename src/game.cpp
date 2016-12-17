#include "game.h"
#include "io.h"

#include "scenes/logos.h"
#include "scenes/splash.h"
#include "scenes/tetris.h"

Game::Game() {
  display = getMainDisplay();
}

void Game::start() {
  currentScene = new LogosScene();
  currentScene->init();
  initButtons();
}

void Game::tick() {
  if(currentScene != NULL) {
    currentScene->tick();
    currentScene->render(display);
    currentScene->isFirstRender = false;
    if(currentScene->nextScene != NULL) {
      Scene * oldScene = currentScene;
      currentScene = oldScene->nextScene;
      currentScene->init();
      delete oldScene;
    } else if(currentScene->goToSplashScreen == true) {
      Scene * oldScene = currentScene;
      delete oldScene;
      currentScene = new SplashScene();
      currentScene->init();
    } else if(currentScene->goToTetrisScreen == true) {
      Scene * oldScene = currentScene;
      delete oldScene;
      currentScene = new TetrisScene();
      currentScene->init();
    }
  }
}

void Game::setScene(Scene * scene) {
  currentScene = scene;
  currentScene->init();
}