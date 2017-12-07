#ifndef GLES3JNI_BUILDINGSELECTEDGAMESTATE_H
#define GLES3JNI_BUILDINGSELECTEDGAMESTATE_H


#include "IdleGameState.h"

class BuildingSelectedGameState : public IdleGameState {
public:
	BuildingSelectedGameState(Game* game, Building* selectedBuilding);

protected:
	Building* selectedBuilding;

	virtual void onPressHex(MapHex* pressedHex);
};


#endif //GLES3JNI_BUILDINGSELECTEDGAMESTATE_H
