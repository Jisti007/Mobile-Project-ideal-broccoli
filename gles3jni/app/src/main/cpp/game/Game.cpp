#include "Game.h"
#include <GLES3/gl3.h>

Game::Game(AssetManager *assetManager) {
	this->assetManager = assetManager;
	map = new GameMap();

	Texture* texture = assetManager->loadTexture("Hex.png");
}

Game::~Game() {
	delete map;
}

void Game::update() {

}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
}
