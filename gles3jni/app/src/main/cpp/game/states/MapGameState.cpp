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
	auto hex = map->getHexSafely(gridPosition);
	if (hex != nullptr) {
		auto unit = hex->getUnit();
		if (unit != nullptr) {
			selectedUnit = unit;
		} else if (selectedUnit != nullptr) {
			selectedUnit->moveTo(hex);
		}
	}

	return true;
}
