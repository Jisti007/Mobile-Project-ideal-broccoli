#include "Game.h"
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
		state = std::make_unique<MapGameState>(&assetManager, &map);
		previousTime =  Clock::now();
	}
}

void Game::update() {
	auto currentTime = Clock::now();
	std::chrono::duration<float> deltaTime = currentTime - previousTime;
	state->update(deltaTime.count());
	previousTime = currentTime;
}

void Game::draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	state->draw(&pipeline);
}
