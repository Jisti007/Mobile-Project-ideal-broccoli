#ifndef GLES3JNI_UISPRITE_H
#define GLES3JNI_UISPRITE_H

#include "UIObject.h"

class UISprite : public UIObject {
public:
	UISprite(Sprite* sprite, glm::vec2 position = {0,0}, glm::vec2 size = {0,0});
	virtual ~UISprite();

	virtual void onDraw(Pipeline* pipeline);

	inline Sprite* getSprite() { return sprite;}

private:
	Sprite* sprite;
};

#endif //GLES3JNI_UISPRITE_H
