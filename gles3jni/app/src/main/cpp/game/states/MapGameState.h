#ifndef GLES3JNI_MAPGAMESTATE_H
#define GLES3JNI_MAPGAMESTATE_H

#include "../AssetManager.h"
#include "GameState.h"
#include "../GameMap.h"
#include "../events/Movement.h"
#include "../ui/Label.h"
#include "../ui/ResourcePanel.h"

class MapGameState : public GameState {
public:
	MapGameState(Game* game);
	virtual ~MapGameState();

	virtual void update(float deltaTime);
	virtual void draw(Pipeline* pipeline);
	virtual void move(float dx, float dy);
	virtual bool press(float x, float y);
	virtual void zoom(float scaleFactor);

private:
	ResourcePanel* resourcePanel;
	Unit* selectedUnit = nullptr;
	MapHex* pressedHex = nullptr;
	ScenarioEvent* animatingEvent = nullptr;
	bool fastAnimation = false;
};

#endif //GLES3JNI_MAPGAMESTATE_H
