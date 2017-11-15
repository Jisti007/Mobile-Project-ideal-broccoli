#ifndef GLES3JNI_UISPRITE_H
#define GLES3JNI_UISPRITE_H

#include "UIObject.h"

class UISprite : public UIObject {
public:
	UISprite(Sprite* sprite, glm::vec2 position);
	UISprite(Sprite* sprite, glm::vec2 position, glm::vec2 size);
	UISprite(Sprite* sprite, glm::vec2 position, float scale);
	UISprite(Sprite* sprite, glm::vec2 position, glm::vec2 size, float scale);
	virtual ~UISprite();

	virtual void onDraw(Pipeline* pipeline);

	inline Sprite* getSprite() { return sprite;}

private:
	Sprite* sprite;
	float scale;
};

#endif //GLES3JNI_UISPRITE_H
