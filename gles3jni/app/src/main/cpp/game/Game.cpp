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
	}

	previousTime =  Clock::now();

	/*
	// Testing
	auto map = campaign->getScenario()->getActiveMap();
	auto node1 = map->tryGetHex(0, 0);
	auto node2 = map->tryGetHex(map->getWidth() - 1, map->getHeight() - 1);
	auto t1 = Clock::now();
	for (int i = 0; i < 100; i++) {
		node1->findShortestPath(node2, nullptr);
	}
	auto t2 = Clock::now();
	std::chrono::duration<float> deltaTime = t2 - t1;
	auto count = deltaTime.count();
	// Original 100x: 7.93162822
	*/
}

void Game::step() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	auto currentTime = Clock::now();
	std::chrono::duration<float> deltaTime = currentTime - previousTime;
	if (state) {
		state->update(deltaTime.count());
		pipeline.beginDraw();
		state->draw(&pipeline, deltaTime.count());
		pipeline.endDraw();
	}
	previousTime = currentTime;
}

void Game::resize(int width, int height) {
	pipeline.setViewportSize(width, height);
	state = std::make_unique<MapGameState>(this);
}
