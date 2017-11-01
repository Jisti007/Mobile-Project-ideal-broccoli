#include "GameState.h"

GameState::GameState() {
	uiRoot = std::unique_ptr<UIObject>(new UIObject());
}

GameState::~GameState() {

}

void GameState::draw(Pipeline *pipeline) {
	pipeline->beginDraw({0, 0}, {960, 540});
	uiRoot->draw(pipeline);
	pipeline->endDraw();
}
