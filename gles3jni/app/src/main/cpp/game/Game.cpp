#include "Game.h"
#include "ui/Button.h"
#include "states/MapGameState.h"

using namespace std;

Game::Game() {

}

Game::~Game() {

}

void Game::initialize() {
	pipeline.initialize();

	if (assetManager.isModuleLoaded("modules/default")) {
		assetManager.reloadAll();
	} else {
		assetManager.unloadAll();
		assetManager.loadModule("modules/default");
		map.initialize(160, 160, &assetManager, &pipeline);
	}

	state = std::unique_ptr<GameState>(new MapGameState(&assetManager, &map));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Game::update() {

}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	map.draw();
	state->draw(&pipeline);
}

void Game::onMove(float dx, float dy) {
	map.getCamera()->moveBy({dx, dy});
}

void Game::onResize(int width, int height) {
	map.getCamera()->setSize({width, height});
	glViewport(0, 0, width, height);
}

void Game::onPress(float x, float y) {
	state->press(x, y);
}
