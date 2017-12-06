#ifndef GLES3JNI_PLAYERANIMATIONGAMESTATE_H
#define GLES3JNI_PLAYERANIMATIONGAMESTATE_H

#include "AnimationGameState.h"

class PlayerAnimationGameState : public AnimationGameState {
public:
	PlayerAnimationGameState(Game* game, Unit* selectedUnit);

protected:
	virtual void onAnimationFinished();

private:
	Unit* selectedUnit;
};

#endif //GLES3JNI_PLAYERANIMATIONGAMESTATE_H
