#ifndef GLES3JNI_UNITSELECTEDGAMESTATE_H
#define GLES3JNI_UNITSELECTEDGAMESTATE_H

#include "MapGameState.h"

class UnitSelectedGameState : public MapGameState {
public:
	UnitSelectedGameState(Game* game, Unit* selectedUnit);

protected:
	virtual void onPressHex(MapHex* hex);

private:
	Unit* selectedUnit;
};

#endif //GLES3JNI_UNITSELECTEDGAMESTATE_H
