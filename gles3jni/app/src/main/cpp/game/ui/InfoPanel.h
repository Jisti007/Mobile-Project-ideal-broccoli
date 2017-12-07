#ifndef GLES3JNI_INFOPANEL_H
#define GLES3JNI_INFOPANEL_H

#include "UISprite.h"
#include "../Font.h"
#include "../Unit.h"
#include "Label.h"
#include "Button.h"
#include <sstream>
#include "../states/UnitSelectedGameState.h"

class InfoPanel : public UISprite {
public:
	InfoPanel(Sprite* sprite, glm::vec2 position, Font* font, AssetManager* assetManager, Game* game);
	~InfoPanel();

	void updateInfo();
	void updateInfo(Unit* unit);
	void updateInfo(Building* building);
	void newStringLabel(std::string textString, int skillOffset);
	void newStringLabel(std::string textString, int value, int skillOffset);
	void newStringLabel(std::string textString, float value, int skillOffset);

private:
	Font* font;
	AssetManager* assetManager;
	Game* game;

	Label* nameLabel;
	Label* hpLabel;
	Label* defenseLabel;
	Label* movementLabel;
};


#endif //GLES3JNI_INFOPANEL_H
