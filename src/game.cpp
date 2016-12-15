#include "game.h"
#include "io.h"

#include "scenes/logos.h"

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
    }
  }
}

void Game::setScene(Scene * scene) {
  currentScene = scene;
  currentScene->init();
}