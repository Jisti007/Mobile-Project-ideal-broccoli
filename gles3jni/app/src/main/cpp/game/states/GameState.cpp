#include "GameState.h"

GameState::GameState(Game* game) {
	this->game = game;
	uiRoot = std::make_unique<UIObject>();
}

GameState::~GameState() {

}

void GameState::draw(Pipeline *pipeline) {
	pipeline->beginDraw();
	pipeline->setCameraPosition({0,0});
	uiRoot->draw(pipeline);
	pipeline->endDraw();
}
