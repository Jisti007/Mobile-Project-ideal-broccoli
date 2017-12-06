#ifndef GLES3JNI_IDLEGAMESTATE_H
#define GLES3JNI_IDLEGAMESTATE_H

#include "PlayerGameState.h"

class IdleGameState : public PlayerGameState {
public:
	IdleGameState(Game* game);

	virtual void recreateUI();

private:
	void createUI();
};

#endif //GLES3JNI_IDLEGAMESTATE_H
