#ifndef GLES3JNI_RESOURCEPANEL_H
#define GLES3JNI_RESOURCEPANEL_H

#include "UISprite.h"
#include "../Font.h"
#include "../Scenario.h"
#include "Label.h"

class ResourcePanel : public UISprite {
public:
	ResourcePanel(Sprite* sprite, glm::vec2 position, Font* font, Scenario* scenario);
	~ResourcePanel();
	void updateResources(Scenario* scenario);

private:
	Font* font;
};

#endif //GLES3JNI_RESOURCEPANEL_H
