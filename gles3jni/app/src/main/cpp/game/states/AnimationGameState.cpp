#include "AnimationGameState.h"
#include "UnitSelectedGameState.h"

AnimationGameState::AnimationGameState(Game* game, Unit* selectedUnit) : PlayerGameState(game) {
	this->selectedUnit = selectedUnit;
}

void AnimationGameState::update(float deltaTime) {
	PlayerGameState::update(deltaTime);
	auto scene = game->getCampaign()->getScenario()->getActiveMap()->getScene();
	if (fastAnimation) {
		deltaTime *= 16;
	}
	if (!scene->animate(deltaTime)) {
		if (selectedUnit != nullptr) {
			std::unique_ptr<GameState> unitSelectedGameState(
				new UnitSelectedGameState(game, selectedUnit)
			);
			game->changeState(unitSelectedGameState);
		} else {
			std::unique_ptr<GameState> mapGameState(
				new PlayerGameState(game)
			);
			game->changeState(mapGameState);
		}
	}
}

bool AnimationGameState::press(float x, float y) {
	fastAnimation = true;
	return true;
}
