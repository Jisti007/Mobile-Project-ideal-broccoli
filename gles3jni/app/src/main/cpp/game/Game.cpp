#include "Game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::initialize() {
	pipeline.initialize();
	assetManager.loadModule("modules/default");
	map.initialize(8, 8, assetManager, &pipeline);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void Game::update() {

}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	map.draw();
}

void Game::onMove(float dx, float dy) {
	map.getScene()->getCamera()->moveBy({dx, dy});
}

void Game::onResize(int width, int height) {
	map.getScene()->getCamera()->setSize({width, height});
}
