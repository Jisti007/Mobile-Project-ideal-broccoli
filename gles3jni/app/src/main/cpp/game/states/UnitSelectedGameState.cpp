#include "UnitSelectedGameState.h"
#include "../events/Attack.h"
#include "AnimationGameState.h"
#include "PathSelectedGameState.h"
#include "TargetSelectedGameState.h"

UnitSelectedGameState::UnitSelectedGameState(Game* game, Unit* selectedUnit) : IdleGameState(game) {
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
		} else {
			game->changeToNew<UnitSelectedGameState>(game, unit);
		}
	} else {
		auto selectedUnitHex = map->tryGetHex(selectedUnit->getGridPosition());
		auto path = selectedUnitHex->findShortestPath(pressedHex, selectedUnit);
		game->changeToNew<PathSelectedGameState>(game, path, selectedUnit);
	}
}

