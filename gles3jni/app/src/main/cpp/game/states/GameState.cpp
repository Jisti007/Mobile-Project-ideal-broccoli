#include "GameState.h"

GameState::GameState(Game* game) {
	this->game = game;
	uiRoot = std::make_unique<UIObject>();
}

GameState::~GameState() {

}

void GameState::draw(Pipeline *pipeline) {
	pipeline->setCameraPosition({0, 0});
	pipeline->setCameraZoom(1.0f);
	uiRoot->draw(pipeline);
}
