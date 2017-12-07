//
// Created by K1697 on 29.11.2017.
//

#ifndef GLES3JNI_UNITINFOGAMESTATE_H
#define GLES3JNI_UNITINFOGAMESTATE_H

#include "PlayerGameState.h"

class UnitInfoGameState : public PlayerGameState {
public:
	UnitInfoGameState(Game* game, Unit* selectedUnit);

private:
	Unit* selectedUnit;
	Building* selectedBuilding;
};


#endif //GLES3JNI_PLAYERGAMESTATE_H
