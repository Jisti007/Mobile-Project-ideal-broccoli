#include "BuildingInfoGameState.h"

BuildingInfoGameState::BuildingInfoGameState(Game* game, Building* selectedBuilding) : PlayerGameState(game) {
	this->selectedBuilding = selectedBuilding;
}
