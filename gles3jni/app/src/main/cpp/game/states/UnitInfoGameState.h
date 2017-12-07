#ifndef GLES3JNI_UNITINFOGAMESTATE_H
#define GLES3JNI_UNITINFOGAMESTATE_H

#include "PlayerGameState.h"
#include "../ui/InfoPanel.h"

class UnitInfoGameState : public PlayerGameState {
public:
	UnitInfoGameState(Game* game, Unit* selectedUnit);

	virtual void recreateUI();

	virtual void move(float dx, float dy);
	virtual bool press(float x, float y);
	virtual void zoom(float scaleFactor);
private:
	Unit* selectedUnit;
	InfoPanel* infoPanel;
	void createUI();
};


#endif //GLES3JNI_PLAYERGAMESTATE_H
