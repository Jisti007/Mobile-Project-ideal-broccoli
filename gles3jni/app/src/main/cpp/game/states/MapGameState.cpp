#include <sstream>
#include "MapGameState.h"
#include "../ui/Button.h"
#include "../events/Movement.h"
#include "../ui/Label.h"
#include "../ui/ResourcePanel.h"
#include "../scenes/MovementAnimation.h"
#include "../events/Attack.h"
#include "UnitSelectedGameState.h"
#include "../ui/RecoloredUISprite.h"
#include <algorithm>

MapGameState::MapGameState(Game* game)
	: GameState(game) {

}

MapGameState::~MapGameState() {

}

void MapGameState::draw(Pipeline* pipeline, float deltaTime) {
	auto map = game->getCampaign()->getScenario()->getActiveMap();
	map->draw(deltaTime);
	GameState::draw(pipeline, deltaTime);
}

void MapGameState::move(float dx, float dy) {
	auto scene = game->getCampaign()->getScenario()->getActiveMap()->getScene();
	auto camera = scene->getCamera();
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
	auto scene = game->getCampaign()->getScenario()->getActiveMap()->getScene();
	auto camera = scene->getCamera();
	camera->scaleZoom(scaleFactor);
}
