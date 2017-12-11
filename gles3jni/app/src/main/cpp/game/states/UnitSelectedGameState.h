#ifndef GLES3JNI_UNITSELECTEDGAMESTATE_H
#define GLES3JNI_UNITSELECTEDGAMESTATE_H

#include "MapGameState.h"
#include "PlayerGameState.h"
#include "IdleGameState.h"

class UnitSelectedGameState : public IdleGameState {
public:
	UnitSelectedGameState(Game* game, Unit* selectedUnit);

	virtual void recreateUI();

protected:
	Unit* selectedUnit;

	virtual void onPressHex(MapHex* pressedHex);

private:
	void createUI();
	void exitStateButton_onPress(void* args);
};

#endif //GLES3JNI_UNITSELECTEDGAMESTATE_H
