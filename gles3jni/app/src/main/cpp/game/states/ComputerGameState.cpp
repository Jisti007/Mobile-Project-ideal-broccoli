#include "ComputerGameState.h"

ComputerGameState::ComputerGameState(Game* game) : AnimationGameState(game, nullptr) {

}

void ComputerGameState::update(float deltaTime) {


	AnimationGameState::update(deltaTime);
}
