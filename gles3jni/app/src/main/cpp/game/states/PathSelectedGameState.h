#ifndef GLES3JNI_PATHSELECTEDGAMESTATE_H
#define GLES3JNI_PATHSELECTEDGAMESTATE_H

#include "UnitSelectedGameState.h"

class PathSelectedGameState : public UnitSelectedGameState {
public:
	PathSelectedGameState(Game* game, Path path, Unit* selectedUnit);

	virtual void draw(Pipeline* pipeline, float deltaTime);

protected:
	virtual void onPressHex(MapHex* pressedHex);

private:
	Path path;
};

#endif //GLES3JNI_PATHSELECTEDGAMESTATE_H
