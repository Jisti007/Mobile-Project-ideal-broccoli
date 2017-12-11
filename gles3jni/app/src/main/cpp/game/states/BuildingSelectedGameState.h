#ifndef GLES3JNI_BUILDINGSELECTEDGAMESTATE_H
#define GLES3JNI_BUILDINGSELECTEDGAMESTATE_H


#include "IdleGameState.h"

class BuildingSelectedGameState : public IdleGameState {
public:
	BuildingSelectedGameState(Game* game, Building* selectedBuilding);

	virtual void recreateUI();

protected:
	virtual void onPressHex(MapHex* pressedHex);

private:
	Building* selectedBuilding;

	void createUI();
	void exitStateButton_onPress(void* args);
};


#endif //GLES3JNI_BUILDINGSELECTEDGAMESTATE_H
