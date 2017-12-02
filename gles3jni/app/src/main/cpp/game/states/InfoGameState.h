#ifndef GLES3JNI_INFOGAMESTATE_H
#define GLES3JNI_INFOGAMESTATE_H

#include "PlayerGameState.h"

class InfoGameState : public PlayerGameState {
public:
	InfoGameState(Game* game, Unit* selectedUnit);
	InfoGameState(Game* game, Building* selectedBuilding);

private:
	Unit* selectedUnit;
	Building* selectedBuilding;
};


#endif //GLES3JNI_PLAYERGAMESTATE_H
