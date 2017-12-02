#ifndef GLES3JNI_PLAYERGAMESTATE_H
#define GLES3JNI_PLAYERGAMESTATE_H

#include "../AssetManager.h"
#include "../GameMap.h"
#include "../events/Movement.h"
#include "../ui/Label.h"
#include "../ui/ResourcePanel.h"
#include "MapGameState.h"

class PlayerGameState : public MapGameState {

public:
	PlayerGameState(Game* game);
	virtual ~PlayerGameState();

	virtual void recreateUI();
	virtual void update(float deltaTime);

protected:
	virtual void onPressHex(MapHex* hex);

private:
	ResourcePanel* resourcePanel;

	void createUI();
};


#endif //GLES3JNI_PLAYERGAMESTATE_H
