#ifndef GLES3JNI_INFOPANEL_H
#define GLES3JNI_INFOPANEL_H

#include "UISprite.h"
#include "../Font.h"
#include "../Unit.h"
#include "Label.h"
#include "Button.h"
#include <sstream>
#include "../states/UnitSelectedGameState.h"

struct BuildingRecruitment {
	Building* building;
	Recruitment* recruit;
};

class InfoPanel : public UISprite {
public:
	InfoPanel(Sprite* sprite, glm::vec2 position, Font* font, AssetManager* assetManager, Game* game);

	void updateInfo(Unit* unit);
	void updateInfo(Building* building);
	void updateInfo(Building* building, std::vector<Recruitment> recruitment);

private:
	Font* font;
	AssetManager* assetManager;
	Game* game;
	std::vector<BuildingRecruitment> recruitmentList;

	Label* infoLabel;
	Label* skillLabel;

	void recruitButton_onPress(void* recruitArg);
};


#endif //GLES3JNI_INFOPANEL_H
