#include "MapGameState.h"
#include "../ui/Button.h"
#include "../events/Movement.h"
#include "../ui/Label.h"

MapGameState::MapGameState(Game* game)
	: GameState(game) {
	auto assets = game->getAssets();
	auto map = game->getCampaign()->getScenario()->getActiveMap();
	auto viewport = game->getPipeline()->getViewport();

	auto buttonSprite = assets->getSprite("test_button");
	std::unique_ptr<UIObject> button(new Button(
		buttonSprite, glm::vec2{
			viewport.getLeft() + buttonSprite->getWidth() / 2.0f,
			viewport.getTop() - buttonSprite->getHeight() / 2.0f
		}
	));
	button->setOnPress(std::bind(&GameMap::generate, map));
	uiRoot->addChild(button);

	auto resourceSprite = assets->getSprite("ui_resource");
	auto resourceInfo = new UISprite(
		assets->getSprite("ui_resource"), glm::vec2{
			0, viewport.getTop() - resourceSprite->getHeight() / 2.0f}
	);
	std::unique_ptr<UIObject> resourceInfoPointer(resourceInfo);
	uiRoot->addChild(resourceInfoPointer);


	std::unique_ptr<UIObject> resourceLabel(new Label(
		u8"609", assets->getFont("default"),
		glm::vec2{resourceInfo->getLeft() + 50, viewport.getTop() - resourceSprite->getHeight() / 2.0f},
		glm::vec2{400,200}
	));
	resourceInfo->addChild(resourceLabel);




}

MapGameState::~MapGameState() {

}

void MapGameState::update(float deltaTime) {
	if (movement) {
		if (fastAnimation) {
			deltaTime *= 16;
		}
		if (movement->animate(deltaTime)) {
			movement = nullptr;
		}
	}
}

void MapGameState::draw(Pipeline* pipeline) {
	game->getCampaign()->getScenario()->getActiveMap()->draw();
	GameState::draw(pipeline);
}

void MapGameState::move(float dx, float dy) {
	game->getCampaign()->getScenario()->getActiveMap()->getCamera()->moveBy({dx, dy});
}

bool MapGameState::press(float x, float y) {
	if (GameState::press(x, y)) {
		return true;
	}

	if (movement != nullptr) {
		fastAnimation = true;
		return true;
	}

	auto map = game->getCampaign()->getScenario()->getActiveMap();
	auto gridPosition = map->getGridPosition({x, y});
	auto hex = map->tryGetHex(gridPosition);
	if (hex != nullptr) {
		auto unit = hex->getUnit();
		if (unit != nullptr) {
			selectedUnit = unit;
		} else if (selectedUnit != nullptr) {
			auto selectedUnitHex = map->tryGetHex(selectedUnit->getGridPosition());
			auto path = selectedUnitHex->findShortestPath(hex, selectedUnit);
			movement = std::make_unique<Movement>(selectedUnit, path);
			movement->beginAnimation();
			movement->execute();
			fastAnimation = false;
		}
	}

	return true;
}
