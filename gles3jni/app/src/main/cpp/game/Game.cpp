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
		campaign = std::make_unique<Campaign>(this);
		//map.initialize(160, 160, &assetManager, &pipeline);
		previousTime =  Clock::now();
	}
}

void Game::update() {
	auto currentTime = Clock::now();
	std::chrono::duration<float> deltaTime = currentTime - previousTime;
	if (state) {
		state->update(deltaTime.count());
	}
	previousTime = currentTime;
}

void Game::draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	if (state) {
		state->draw(&pipeline);
	}
}

void Game::resize(int width, int height) {
	pipeline.setViewportSize(width, height);
	state = std::make_unique<MapGameState>(this);
}
