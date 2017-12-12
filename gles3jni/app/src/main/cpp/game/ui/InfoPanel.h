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
	BuildingRecruitment(Building* building, Recruitment recruitment) :
		recruitment(recruitment)
	{
		this->building = building;
	}

	Building* building;
	Recruitment recruitment;
};

class InfoPanel : public UISprite {
public:
	InfoPanel(Sprite* sprite, glm::vec2 position, Font* font, AssetManager* assetManager, Game* game);

	void updateInfo(Unit* unit);
	void updateInfo(Building* building);

private:
	Font* font;
	AssetManager* assetManager;
	Game* game;
	std::vector<std::unique_ptr<BuildingRecruitment>> recruitmentList;

	Label* infoLabel;
	Label* skillLabel;

	void recruitButton_onPress(void* recruitArg);
};


#endif //GLES3JNI_INFOPANEL_H
