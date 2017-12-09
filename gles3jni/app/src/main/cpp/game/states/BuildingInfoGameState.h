#ifndef GLES3JNI_BUILDINGINFOGAMESTATE_H
#define GLES3JNI_BUILDINGINFOGAMESTATE_H


#include "PlayerGameState.h"
#include "../ui/InfoPanel.h"

class BuildingInfoGameState : public PlayerGameState {
public:
	BuildingInfoGameState(Game* game, Building* selectedBuilding);

	virtual void recreateUI();

	virtual void move(float dx, float dy);
	virtual bool press(float x, float y);
	virtual void zoom(float scaleFactor);
private:
	Building* selectedBuilding;
	//InfoPanel* infoPanel;
	void createUI();
};


#endif //GLES3JNI_BUILDINGINFOGAMESTATE_H
