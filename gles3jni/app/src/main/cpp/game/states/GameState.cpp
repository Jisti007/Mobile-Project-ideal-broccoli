#include "GameState.h"

GameState::GameState(Game* game) {
	this->game = game;
	createUI();
}

GameState::~GameState() {

}

void GameState::recreateUI() {
	createUI();
}

void GameState::draw(Pipeline *pipeline, float deltaTime) {
	pipeline->setCameraPosition({0, 0});
	pipeline->setCameraZoom(1.0f);
	uiRoot->draw(pipeline);
}

void GameState::createUI() {
	uiRoot = std::make_unique<UIObject>();
}
