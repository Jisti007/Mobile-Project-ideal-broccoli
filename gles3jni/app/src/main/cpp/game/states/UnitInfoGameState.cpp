//
// Created by K1697 on 29.11.2017.
//

#include "UnitInfoGameState.h"

UnitInfoGameState::UnitInfoGameState(Game* game, Unit* selectedUnit) : PlayerGameState(game) {
	this->selectedUnit = selectedUnit;
}


