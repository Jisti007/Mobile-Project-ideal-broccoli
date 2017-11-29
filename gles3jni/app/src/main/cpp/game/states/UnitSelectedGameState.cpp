#include "UnitSelectedGameState.h"
#include "../events/Attack.h"
#include "AnimationGameState.h"

UnitSelectedGameState::UnitSelectedGameState(Game* game, Unit* selectedUnit) : MapGameState(game) {
	this->selectedUnit = selectedUnit;
}

void UnitSelectedGameState::onPressHex(MapHex* pressedHex) {
	debugHex = pressedHex;

	auto scenario = game->getCampaign()->getScenario();
	auto activeFaction = scenario->getActiveFaction();
	auto map = scenario->getActiveMap();
	auto unit = pressedHex->getUnit();
	if (unit != nullptr) {
		if (unit->getFaction() != activeFaction) {
			auto selectedUnitHex = map->tryGetHex(selectedUnit->getGridPosition());
			auto distance = selectedUnitHex->getDistance(pressedHex);
			if (distance <= unit->getType()->getRange()) {
				std::unique_ptr<ScenarioEvent> attack(new Attack(selectedUnit, unit, 2));
				scenario->executeEvent(attack);

				std::unique_ptr<GameState> animationGameState(
					new AnimationGameState(game, selectedUnit)
				);
				game->changeState(animationGameState);
			}
		} else {
			std::unique_ptr<GameState> unitSelectedState(new UnitSelectedGameState(game, unit));
			game->changeState(unitSelectedState);
		}
	} else {
		auto selectedUnitHex = map->tryGetHex(selectedUnit->getGridPosition());
		auto path = selectedUnitHex->findShortestPath(pressedHex, selectedUnit);
		std::unique_ptr<ScenarioEvent> movement(new Movement(
			selectedUnit, path
		));
		scenario->executeEvent(movement);

		std::unique_ptr<GameState> animationGameState(
			new AnimationGameState(game, selectedUnit)
		);
		game->changeState(animationGameState);
	}
}

