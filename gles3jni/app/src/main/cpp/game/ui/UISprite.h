#ifndef GLES3JNI_UISPRITE_H
#define GLES3JNI_UISPRITE_H

#include "UIObject.h"
#include "../Transform2D.h"

class UISprite : public UIObject {
public:
	UISprite(Sprite* sprite, glm::vec2 position);
	UISprite(Sprite* sprite, glm::vec2 position, glm::vec2 size);
	UISprite(Sprite* sprite, Transform2D transform);
	UISprite(Sprite* sprite, glm::vec2 position, glm::vec2 size, glm::vec2 scale);
	virtual ~UISprite();

	virtual void onDraw(Pipeline* pipeline);

	inline Sprite* getSprite() { return sprite;}
	inline glm::vec2 getScale() { return scale; }

private:
	Sprite* sprite;
	glm::vec2 scale;
};

#endif //GLES3JNI_UISPRITE_H
