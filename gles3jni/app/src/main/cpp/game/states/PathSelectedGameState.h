#ifndef GLES3JNI_PATHSELECTEDGAMESTATE_H
#define GLES3JNI_PATHSELECTEDGAMESTATE_H

#include "PlayerGameState.h"

class PathSelectedGameState : public PlayerGameState {
public:
	PathSelectedGameState(Game* game, std::list<Link*> path);

	virtual void draw(Pipeline* pipeline, float deltaTime);

protected:
	virtual void onPressHex(MapHex* pressedHex);

private:
	std::list<Link*> path;
};

#endif //GLES3JNI_PATHSELECTEDGAMESTATE_H
