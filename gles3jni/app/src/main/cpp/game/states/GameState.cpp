#include "GameState.h"

GameState::GameState(Game* game) {
	this->game = game;
	uiRoot = std::make_unique<UIObject>();
}

GameState::~GameState() {

}

void GameState::draw(Pipeline *pipeline) {
	pipeline->setCamera(&camera);
	uiRoot->draw(pipeline);
}
