#ifndef GLES3JNI_MAPGAMESTATE_H
#define GLES3JNI_MAPGAMESTATE_H

#include "../AssetManager.h"
#include "GameState.h"
#include "../GameMap.h"
#include "../events/Movement.h"

class MapGameState : public GameState {
public:
	MapGameState(Game* game);
	virtual ~MapGameState();

	virtual void update(float deltaTime);
	virtual void draw(Pipeline* pipeline);
	virtual void move(float dx, float dy);
	virtual bool press(float x, float y);

private:
	Unit* selectedUnit = nullptr;
	ScenarioEvent* animatingEvent = nullptr;
	bool fastAnimation = false;
};

#endif //GLES3JNI_MAPGAMESTATE_H
