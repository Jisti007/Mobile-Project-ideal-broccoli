#ifndef GLES3JNI_MAPGAMESTATE_H
#define GLES3JNI_MAPGAMESTATE_H

#include "GameState.h"

class MapGameState : public GameState {
public:
	MapGameState(Game* game);
	virtual ~MapGameState();

	virtual void draw(Pipeline* pipeline, float deltaTime);
	virtual void move(float dx, float dy);
	virtual bool press(float x, float y);
	virtual void zoom(float scaleFactor);
protected:
	virtual void onPressHex(MapHex* hex) = 0;
};

#endif //GLES3JNI_MAPGAMESTATE_H
