#include "PathSelectedGameState.h"
#include "AnimationGameState.h"
#include "../pathing/MovementLink.h"
#include <vector>
#include "../../glm/glm.hpp"

PathSelectedGameState::PathSelectedGameState(Game* game, Path path, Unit* selectedUnit)
	: path(path), UnitSelectedGameState(game, selectedUnit) {
}

void PathSelectedGameState::draw(Pipeline* pipeline, float deltaTime) {
	auto map = game->getCampaign()->getScenario()->getActiveMap();
	map->draw(deltaTime);

	auto pathMarker = game->getAssets()->getSprite("dot_marker");
	auto costSoFar = 0.0f;
	for (auto& link : path.getLinks()) {
		costSoFar += link->getCost(selectedUnit, costSoFar);
		auto hex = static_cast<MapHex*>(link->getDestination());
		auto position = hex->getActor()->getPosition();
		if (costSoFar <= selectedUnit->getMovement()) {
			pipeline->setAmbientColor({1.0f, 1.0f, 0.0f});
		} else {
			pipeline->setAmbientColor({1.0f, 0.0f, 0.0f});
		}
		pipeline->draw(pathMarker, position);
	}
	pipeline->setAmbientColor({1.0f, 1.0f, 1.0f});
	GameState::draw(pipeline, deltaTime);
}

void PathSelectedGameState::onPressHex(MapHex* pressedHex) {
	auto scenario = game->getCampaign()->getScenario();
	if (pressedHex == path.getLinks().back()->getDestination()) {
		if (path.getCost() <= selectedUnit->getMovement()) {
			std::unique_ptr<ScenarioEvent> movement(new Movement(
				selectedUnit, path
			));
			scenario->executeEvent(movement);

			std::unique_ptr<GameState> animationGameState(
				new AnimationGameState(game, selectedUnit)
			);
			game->changeState(animationGameState);
		}
	} else {
		UnitSelectedGameState::onPressHex(pressedHex);
	}
}
