//
// Created by K1697 on 7.12.2017.
//

#include "BuildingInfoGameState.h"

BuildingInfoGameState::BuildingInfoGameState(Game* game, Building* selectedBuilding) : PlayerGameState(game) {
	this->selectedBuilding = selectedBuilding;
}
