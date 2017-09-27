#include "Game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::initialize() {
	Scene::initializePipeline();
	assetManager.loadModule("modules/default");
	map.initialize(32, 32, assetManager);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void Game::update() {

}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	map.draw();
}
