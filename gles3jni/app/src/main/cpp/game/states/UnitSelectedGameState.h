#ifndef GLES3JNI_UNITSELECTEDGAMESTATE_H
#define GLES3JNI_UNITSELECTEDGAMESTATE_H

#include "MapGameState.h"
#include "PlayerGameState.h"

class UnitSelectedGameState : public PlayerGameState {
public:
	UnitSelectedGameState(Game* game, Unit* selectedUnit);

protected:
	virtual void onPressHex(MapHex* pressedHex);

private:
	Unit* selectedUnit;
};

#endif //GLES3JNI_UNITSELECTEDGAMESTATE_H
