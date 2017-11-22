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

	virtual void recreateUI();
	virtual void update(float deltaTime);
	virtual void draw(Pipeline* pipeline, float deltaTime);
	virtual void move(float dx, float dy);
	virtual bool press(float x, float y);
	virtual void zoom(float scaleFactor);

protected:
	MapHex* debugHex = nullptr;

	virtual void onPressHex(MapHex* hex);

private:
	ResourcePanel* resourcePanel;

	void createUI();
};

#endif //GLES3JNI_MAPGAMESTATE_H
