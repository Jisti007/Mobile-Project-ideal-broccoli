#include "PlayerAnimationGameState.h"
#include "UnitSelectedGameState.h"

PlayerAnimationGameState::PlayerAnimationGameState(Game* game, Unit* selectedUnit)
	: AnimationGameState(game) {
	this->selectedUnit = selectedUnit;
}

void PlayerAnimationGameState::onAnimationFinished() {
	if (selectedUnit != nullptr) {
		game->changeToNew<UnitSelectedGameState>(game, selectedUnit);
	} else {
		game->changeToNew<PlayerGameState>(game);
	}
}
