#ifndef GLES3JNI_UNITINFOGAMESTATE_H
#define GLES3JNI_UNITINFOGAMESTATE_H

#include "PlayerGameState.h"
#include "../ui/InfoPanel.h"

class UnitInfoGameState : public PlayerGameState {
public:
	UnitInfoGameState(Game* game, Unit* selectedUnit);

	void createInfo(Unit* selectedUnit);

private:
	Unit* selectedUnit;
	InfoPanel* infoPanel;
};


#endif //GLES3JNI_PLAYERGAMESTATE_H
