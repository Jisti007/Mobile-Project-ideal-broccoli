#ifndef GLES3JNI_ANIMATIONGAMESTATE_H
#define GLES3JNI_ANIMATIONGAMESTATE_H

#include "MapGameState.h"
#include "PlayerGameState.h"

class AnimationGameState : public PlayerGameState {
public:
	AnimationGameState(Game* game);

	virtual void update(float deltaTime);
	virtual bool press(float x, float y);

protected:
	virtual void onAnimationFinished() = 0;

private:
	bool fastAnimation = false;
};

#endif //GLES3JNI_ANIMATIONGAMESTATE_H
