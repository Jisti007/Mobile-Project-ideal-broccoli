#ifndef GLES3JNI_PATHSELECTEDGAMESTATE_H
#define GLES3JNI_PATHSELECTEDGAMESTATE_H

#include "MapGameState.h"

class PathSelectedGameState : public MapGameState {
public:
	PathSelectedGameState(Game* game, std::list<Link*> path);

	virtual void draw(Pipeline* pipeline, float deltaTime);

protected:
	virtual void onPressHex(MapHex* pressedHex);

private:
	std::list<Link*> path;
};

#endif //GLES3JNI_PATHSELECTEDGAMESTATE_H
