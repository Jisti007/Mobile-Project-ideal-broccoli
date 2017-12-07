#ifndef GLES3JNI_UNITSELECTEDGAMESTATE_H
#define GLES3JNI_UNITSELECTEDGAMESTATE_H

#include "MapGameState.h"
#include "PlayerGameState.h"
#include "IdleGameState.h"

class UnitSelectedGameState : public IdleGameState {
public:
	UnitSelectedGameState(Game* game, Unit* selectedUnit);

protected:
	Unit* selectedUnit;

	virtual void onPressHex(MapHex* pressedHex);
};

#endif //GLES3JNI_UNITSELECTEDGAMESTATE_H
