#ifndef GLES3JNI_TARGETSELECTEDGAMESTATE_H
#define GLES3JNI_TARGETSELECTEDGAMESTATE_H

#include "UnitSelectedGameState.h"

class TargetSelectedGameState : public UnitSelectedGameState {
public:
	TargetSelectedGameState(Game* game, Unit* selectedUnit, Unit* target);

	virtual void recreateUI();
	virtual void move(float dx, float dy);

private:
	Unit* target;

	void createUI();
};

#endif //GLES3JNI_TARGETSELECTEDGAMESTATE_H
