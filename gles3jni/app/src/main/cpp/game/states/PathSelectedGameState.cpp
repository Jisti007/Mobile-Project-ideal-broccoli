#include "PathSelectedGameState.h"
#include "AnimationGameState.h"

PathSelectedGameState::PathSelectedGameState(Game* game, std::list<Link*> path)
	: MapGameState(game) {
	this->path = path;
}

void PathSelectedGameState::draw(Pipeline* pipeline, float deltaTime) {
	auto pathMarker = game->getAssets()->getSprite("dot_marker");
	auto map = game->getCampaign()->getScenario()->getActiveMap();
	map->draw(deltaTime);
	for (auto& node : path) {
		auto hex = static_cast<MapHex*>(node->getDestination());
		auto position = hex->getActor()->getPosition();
		pipeline->draw(pathMarker, position);
	}
	GameState::draw(pipeline, deltaTime);
}

void PathSelectedGameState::onPressHex(MapHex* pressedHex) {
	auto selectedUnitHex = static_cast<MapHex*>(path.front()->getSource());
	auto selectedUnit = selectedUnitHex->getUnit();

	if (pressedHex == path.back()->getDestination()) {
		std::unique_ptr<ScenarioEvent> movement(new Movement(
			selectedUnit, path
		));
		game->getCampaign()->getScenario()->executeEvent(movement);

		std::unique_ptr<GameState> animationGameState(
			new AnimationGameState(game, selectedUnit)
		);
		game->changeState(animationGameState);
	} else {
		path = selectedUnitHex->findShortestPath(pressedHex, selectedUnit);
	}
}
