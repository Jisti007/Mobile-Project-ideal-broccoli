#include <sstream>
#include "MapGameState.h"
#include "../ui/Button.h"
#include "../events/Movement.h"
#include "../ui/Label.h"
#include "../ui/ResourcePanel.h"
#include "../scenes/MovementAnimation.h"
#include "../events/Attack.h"
#include "UnitSelectedGameState.h"
#include <algorithm>

MapGameState::MapGameState(Game* game)
	: GameState(game) {
	createUI();
}

MapGameState::~MapGameState() {

}

void MapGameState::recreateUI() {
	GameState::recreateUI();
	createUI();
}

void MapGameState::update(float deltaTime) {
	// TODO: Move to when resources update
	auto scenario = game->getCampaign()->getScenario();
	resourcePanel->updateResources(scenario);
}

void MapGameState::draw(Pipeline* pipeline, float deltaTime) {
	auto map = game->getCampaign()->getScenario()->getActiveMap();
	map->draw(deltaTime);
	if (debugHex != nullptr) {
		auto hexMarkerSprite = game->getAssets()->getSprite("hex_marker");
		auto position = debugHex->getActor()->getPosition();
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

	auto scenario = game->getCampaign()->getScenario();
	/*
	auto activeFaction = scenario->getActiveFaction();
	if (!activeFaction->isPlayer()) {
		return true;
	}
	*/
	auto map = scenario->getActiveMap();
	auto gridPosition = map->getGridPosition({x, y});
	auto hex = map->tryGetHex(gridPosition);
	if (hex != nullptr) {
		onPressHex(hex);
	}

	return true;
}

void MapGameState::zoom(float scaleFactor) {
	auto camera = game->getCampaign()->getScenario()->getActiveMap()->getCamera();
	camera->scaleZoom(scaleFactor);
}

void MapGameState::onPressHex(MapHex* hex) {
	debugHex = hex;

	auto scenario = game->getCampaign()->getScenario();
	auto activeFaction = scenario->getActiveFaction();
	auto unit = hex->getUnit();
	if (unit != nullptr && unit->getFaction() == activeFaction) {
		std::unique_ptr<GameState> unitSelectedState(new UnitSelectedGameState(game, unit));
		game->changeState(unitSelectedState);
	}
}

void MapGameState::createUI() {
	auto assets = game->getAssets();
	auto scenario = game->getCampaign()->getScenario();
	auto map = scenario->getActiveMap();
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

	auto endTurnButtonSprite = assets->getSprite("end_turn_button");
	std::unique_ptr<UIObject> endTurnButton(new Button(
		endTurnButtonSprite, glm::vec2{
			viewport.getLeft() + endTurnButtonSprite->getWidth() / 2.0f,
			viewport.getBottom() + endTurnButtonSprite->getHeight() / 2.0f
		}
	));
	endTurnButton->setOnPress(std::bind(&Scenario::endTurn, scenario));
	uiRoot->addChild(endTurnButton);
}
