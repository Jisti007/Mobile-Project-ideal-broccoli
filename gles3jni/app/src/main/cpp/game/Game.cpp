#include "Game.h"

Game::Game(AssetManager *assetManager) {
	this->assetManager = assetManager;
	map = new GameMap();
}

Game::~Game() {
	delete map;
}

void Game::update() {

}

void Game::draw() {

}
