#ifndef GLES3JNI_ANIMATIONGAMESTATE_H
#define GLES3JNI_ANIMATIONGAMESTATE_H

#include "MapGameState.h"

class AnimationGameState : public MapGameState {
public:
	AnimationGameState(Game* game, Unit* selectedUnit);

	virtual void update(float deltaTime);
	virtual bool press(float x, float y);

private:
	Unit* selectedUnit;
	bool fastAnimation = false;
};

#endif //GLES3JNI_ANIMATIONGAMESTATE_H
