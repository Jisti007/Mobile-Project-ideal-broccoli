#include "UnitSelectedGameState.h"
#include "../events/Attack.h"
#include "AnimationGameState.h"
#include "PathSelectedGameState.h"
#include "TargetSelectedGameState.h"

UnitSelectedGameState::UnitSelectedGameState(Game* game, Unit* selectedUnit) : PlayerGameState(game) {
	this->selectedUnit = selectedUnit;
}

void UnitSelectedGameState::onPressHex(MapHex* pressedHex) {
	auto scenario = game->getCampaign()->getScenario();
	auto activeFaction = scenario->getActiveFaction();
	auto map = scenario->getActiveMap();
	auto unit = pressedHex->getUnit();
	if (unit != nullptr) {
		if (unit->getFaction() != activeFaction) {
			game->changeToNew<TargetSelectedGameState>(game, selectedUnit, unit);
			/*
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
			*/
		} else {
			game->changeToNew<UnitSelectedGameState>(game, unit);
			/*
			std::unique_ptr<GameState> unitSelectedState(new UnitSelectedGameState(game, unit));
			game->changeState(unitSelectedState);
			*/
		}
	} else {
		auto selectedUnitHex = map->tryGetHex(selectedUnit->getGridPosition());
		auto path = selectedUnitHex->findShortestPath(pressedHex, selectedUnit);
		game->changeToNew<PathSelectedGameState>(game, path, selectedUnit);
		/*
		std::unique_ptr<GameState> pathSelectedGameState(
			new PathSelectedGameState(game, path, selectedUnit)
		);
		game->changeState(pathSelectedGameState);
		*/
	}
}

