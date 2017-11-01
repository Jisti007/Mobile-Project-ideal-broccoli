#include "MapGameState.h"
#include "../ui/Button.h"

using namespace std;

MapGameState::MapGameState(AssetManager* assets, GameMap* map) {
	this->map = map;
	this->assets = assets;

	auto button = std::unique_ptr<UIObject>(new Button(
		assets->getSprite("test_button"), glm::vec2{-650,440}, glm::vec2{200,200}
	));
	button->setOnPress(bind(&GameMap::generate, map));
	uiRoot->addChild(std::move(button));
}

MapGameState::~MapGameState() {

}

bool MapGameState::press(float x, float y) {
	if (GameState::press(x, y)) {
		return true;
	}

	auto gridPosition = map->getGridPosition({x, y});
	map->createUnit(gridPosition, assets->getUnitType("test"), map->getFaction(0));

	return true;
}
