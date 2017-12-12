#include "Game.h"
#include "states/MapGameState.h"
#include "states/PlayerGameState.h"
#include "states/IdleGameState.h"
#include "states/MainMenuGameState.h"

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
	auto state = getState();
	if (state) {
		state->update(deltaTime.count());
		pipeline.beginDraw();
		state->draw(&pipeline, deltaTime.count());
		oldStates.clear();
		pipeline.endDraw();
	}
	previousTime = currentTime;
}

void Game::resize(int width, int height) {
	pipeline.setViewportSize(width, height);
	auto state = getState();
	if (state == nullptr) {
		pushNew<MainMenuGameState>(this);
	} else {
		state->recreateUI();
	}
}

void Game::pushState(std::unique_ptr<GameState>& state) {
	states.push_back(std::move(state));
}

void Game::popState() {
	if (states.size() > 1) {
		oldStates.push_back(std::move(states.back()));
		states.pop_back();
	}
}

void Game::changeState(std::unique_ptr<GameState>& state) {
	if (states.size() > 0) {
		oldStates.push_back(std::move(states.back()));
		states.pop_back();
	}
	pushState(state);
}

GameState* Game::getState() {
	if (states.size() > 0) {
		return states.back().get();
	}
	return nullptr;
}
