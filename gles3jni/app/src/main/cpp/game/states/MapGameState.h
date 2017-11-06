#ifndef GLES3JNI_MAPGAMESTATE_H
#define GLES3JNI_MAPGAMESTATE_H

#include "../AssetManager.h"
#include "GameState.h"
#include "../GameMap.h"

class MapGameState : public GameState {
public:
	MapGameState(AssetManager* assets, GameMap* map);
	virtual ~MapGameState();

	virtual void update();
	virtual void draw(Pipeline* pipeline);
	virtual void move(float dx, float dy);
	virtual bool press(float x, float y);

private:
	AssetManager* assets;
	GameMap* map;
	Unit* selectedUnit = nullptr;
};

#endif //GLES3JNI_MAPGAMESTATE_H
