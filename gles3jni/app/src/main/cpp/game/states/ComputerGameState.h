#ifndef GLES3JNI_COMPUTERGAMESTATE_H
#define GLES3JNI_COMPUTERGAMESTATE_H

#include "AnimationGameState.h"

class ComputerGameState : public AnimationGameState {
public:
	ComputerGameState(Game* game);

	virtual void update(float deltaTime);
};

#endif //GLES3JNI_COMPUTERGAMESTATE_H
