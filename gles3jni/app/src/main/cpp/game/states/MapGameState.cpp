#include "MapGameState.h"
#include "../ui/Button.h"

using namespace std;

MapGameState::MapGameState(AssetManager* assets, GameMap* map) {
	auto button = std::unique_ptr<UIObject>(new Button(
		assets->getSprite("test_button"), glm::vec2{-650,440}, glm::vec2{200,200}
	));
	button->setOnPress(bind(&GameMap::generate, map));
	uiRoot->addChild(std::move(button));
}

MapGameState::~MapGameState() {

}
