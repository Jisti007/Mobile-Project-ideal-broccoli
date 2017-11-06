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

	auto resourceInfo = std::unique_ptr<UIObject>(new UISprite(
			assets->getSprite("ui_resource"), glm::vec2{0,440}, glm::vec2{400,200}
	));
	uiRoot->addChild(std::move(resourceInfo));
}

MapGameState::~MapGameState() {

}

bool MapGameState::press(float x, float y) {
	if (GameState::press(x, y)) {
		return true;
	}

	auto gridPosition = map->getGridPosition({x, y});
	auto hex = map->tryGetHex(gridPosition);
	if (hex != nullptr) {
		auto unit = hex->getUnit();
		if (unit != nullptr) {
			selectedUnit = unit;
		} else if (selectedUnit != nullptr) {
			auto selectedUnitHex = map->tryGetHex(selectedUnit->getPosition());
			auto path = selectedUnitHex->findShortestPath(hex, selectedUnit);
			path.pop_front();
			auto nextHex = static_cast<MapHex*>(path.front());
			selectedUnit->moveTo(nextHex);
		}
	}

	return true;
}
