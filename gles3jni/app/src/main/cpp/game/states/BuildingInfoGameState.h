//
// Created by K1697 on 7.12.2017.
//

#ifndef GLES3JNI_BUILDINGINFOGAMESTATE_H
#define GLES3JNI_BUILDINGINFOGAMESTATE_H


#include "PlayerGameState.h"

class BuildingInfoGameState : public PlayerGameState {
public:
	BuildingInfoGameState(Game* game, Building* selectedBuilding);

private:
	Unit* selectedUnit;
	Building* selectedBuilding;
};


#endif //GLES3JNI_BUILDINGINFOGAMESTATE_H
