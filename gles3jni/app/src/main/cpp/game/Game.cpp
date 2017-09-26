#include "Game.h"
#include <GLES3/gl3.h>

Game::Game() {
	map = new GameMap();
}

Game::~Game() {
	delete map;
}

void Game::initialize() {
	assetManager.loadModule("modules/default");
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void Game::update() {

}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
}
