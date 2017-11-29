#ifndef GLES3JNI_PATHSELECTEDGAMESTATE_H
#define GLES3JNI_PATHSELECTEDGAMESTATE_H

#include "PlayerGameState.h"

class PathSelectedGameState : public PlayerGameState {
public:
	PathSelectedGameState(Game* game, std::list<Link*> path, Unit* selectedUnit);

	virtual void draw(Pipeline* pipeline, float deltaTime);

protected:
	virtual void onPressHex(MapHex* pressedHex);

private:
	std::list<Link*> path;
	Unit* selectedUnit = nullptr;
	float pathCost = 0.0f;
};

#endif //GLES3JNI_PATHSELECTEDGAMESTATE_H
