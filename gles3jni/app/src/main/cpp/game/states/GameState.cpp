#include "GameState.h"

GameState::GameState() {
	uiRoot = std::make_unique<UIObject>();
}

GameState::~GameState() {

}

void GameState::draw(Pipeline *pipeline) {
	pipeline->beginDraw({0, 0});
	uiRoot->draw(pipeline);
	pipeline->endDraw();
}
