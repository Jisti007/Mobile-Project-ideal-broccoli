//
// Created by K1697 on 29.11.2017.
//

#include "InfoGameState.h"

InfoGameState::InfoGameState(Game* game, Unit* selectedUnit) : PlayerGameState(game) {
	this->selectedUnit = selectedUnit;
}

InfoGameState::InfoGameState(Game* game, Building* selectedBuilding) : PlayerGameState(game) {
	this->selectedBuilding = selectedBuilding;
}

