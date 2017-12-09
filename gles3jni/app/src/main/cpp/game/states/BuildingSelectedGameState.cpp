#include "BuildingSelectedGameState.h"
#include "BuildingInfoGameState.h"

BuildingSelectedGameState::BuildingSelectedGameState(Game* game, Building* selectedBuilding) : IdleGameState(game) {
	this->selectedBuilding = selectedBuilding;
}

void BuildingSelectedGameState::onPressHex(MapHex* pressedHex) {
	auto scenario = game->getCampaign()->getScenario();
	//auto activeFaction = scenario->getActiveFaction();
	//auto map = scenario->getActiveMap();
	auto building = pressedHex->getBuilding();
	if (building != nullptr){
		if (building == selectedBuilding) {
			game->pushNew<BuildingInfoGameState>(game, selectedBuilding);
		}
	}
}
