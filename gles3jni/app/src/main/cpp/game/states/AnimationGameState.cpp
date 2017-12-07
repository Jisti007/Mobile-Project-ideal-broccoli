#include "AnimationGameState.h"
#include "UnitSelectedGameState.h"

AnimationGameState::AnimationGameState(Game* game) : PlayerGameState(game) {
}

void AnimationGameState::update(float deltaTime) {
	PlayerGameState::update(deltaTime);
	auto scene = game->getCampaign()->getScenario()->getActiveMap()->getScene();
	if (fastAnimation) {
		deltaTime *= 16;
	}
	if (!scene->animate(deltaTime)) {
		onAnimationFinished();
	}
}

bool AnimationGameState::press(float x, float y) {
	fastAnimation = true;
	return true;
}
