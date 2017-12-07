#ifndef GLES3JNI_INFOPANEL_H
#define GLES3JNI_INFOPANEL_H


#include "UISprite.h"
#include "../Font.h"
#include "../Unit.h"
#include "Label.h"
#include "Button.h"

class InfoPanel : public UISprite {
public:
	InfoPanel(Sprite* sprite, glm::vec2 position, Font* font, AssetManager* assetManager);
	~InfoPanel();

	void updateInfo(Unit* unit);

private:
	Font* font;
	AssetManager* assetManager;
};


#endif //GLES3JNI_INFOPANEL_H
