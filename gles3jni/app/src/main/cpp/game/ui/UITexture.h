#ifndef GLES3JNI_UITEXTURE_H
#define GLES3JNI_UITEXTURE_H

#include "UIObject.h"

class UITexture : public UIObject {
public:
	UITexture(Texture* texture, glm::vec2 position = {0,0}, glm::vec2 size = {0,0});

	virtual void onDraw(Pipeline* pipeline);

private:
	Sprite sprite;
};

#endif //GLES3JNI_UITEXTURE_H
