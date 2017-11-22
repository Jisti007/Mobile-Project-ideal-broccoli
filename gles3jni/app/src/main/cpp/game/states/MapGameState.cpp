#include <sstream>
#include "MapGameState.h"
#include "../ui/Button.h"
#include "../events/Movement.h"
#include "../ui/Label.h"
#include "../ui/ResourcePanel.h"
#include "../scenes/MovementAnimation.h"
#include <algorithm>

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

	auto resourcePanelSprite = assets->getSprite("ui_resource");
	resourcePanel = new ResourcePanel(
		resourcePanelSprite, glm::vec2{
			0, viewport.getTop() - resourcePanelSprite->getHeight() / 2.0f
		},
		assets->getFont("default")
	);
	std::unique_ptr<UIObject> resourcePanelPointer(resourcePanel);
	uiRoot->addChild(resourcePanelPointer);
}

MapGameState::~MapGameState() {

}

void MapGameState::update(float deltaTime) {
	auto scenario = game->getCampaign()->getScenario();
	auto scene = scenario->getActiveMap()->getScene();

	if (fastAnimation) {
		deltaTime *= 16;
	}
	animatingEvent = scene->animate(deltaTime);
	if (!animatingEvent) {
		fastAnimation = false;
	}

	// TODO: Move to when resources update
	resourcePanel->updateResources(scenario);
}

void MapGameState::draw(Pipeline* pipeline, float deltaTime) {
	auto map = game->getCampaign()->getScenario()->getActiveMap();
	map->draw(deltaTime);
	if (pressedHex != nullptr) {
		auto hexMarkerSprite = game->getAssets()->getSprite("hex_marker");
		auto position = pressedHex->getActor()->getPosition();
		pipeline->draw(hexMarkerSprite, position, 1.0f);
	}
	GameState::draw(pipeline, deltaTime);
}

void MapGameState::move(float dx, float dy) {
	auto camera = game->getCampaign()->getScenario()->getActiveMap()->getCamera();
	auto zoom = camera->getZoom();
	dx /= zoom * GameMap::gridSize;
	dy /= zoom * GameMap::gridSize;
	camera->moveBy({dx, dy});
}

bool MapGameState::press(float x, float y) {
	if (GameState::press(x, y)) {
		return true;
	}

	if (animatingEvent) {
		fastAnimation = true;
		return true;
	}

	auto scenario = game->getCampaign()->getScenario();
	auto activeFaction = scenario->getActiveFaction();
	if (!activeFaction->isPlayer()) {
		return true;
	}

	auto map = scenario->getActiveMap();
	auto gridPosition = map->getGridPosition({x, y});
	auto hex = map->tryGetHex(gridPosition);
	if (hex != nullptr) {
		pressedHex = hex;
		auto unit = hex->getUnit();
		if (unit != nullptr) {
			if (unit->getFaction() == activeFaction) {
				selectedUnit = unit;
			}
		} else if (selectedUnit != nullptr) {
			auto selectedUnitHex = map->tryGetHex(selectedUnit->getGridPosition());
			auto path = selectedUnitHex->findShortestPath(hex, selectedUnit);
			std::unique_ptr<ScenarioEvent> movement(new Movement(
				selectedUnit, path
			));
			scenario->executeEvent(movement);
			fastAnimation = false;
		}
	}

	return true;
}

void MapGameState::zoom(float scaleFactor) {
	auto camera = game->getCampaign()->getScenario()->getActiveMap()->getCamera();
	camera->scaleZoom(scaleFactor);
}
