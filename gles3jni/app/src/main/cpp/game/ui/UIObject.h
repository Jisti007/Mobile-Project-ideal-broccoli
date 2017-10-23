//
// Created by K1697 on 20.10.2017.
//

#ifndef GLES3JNI_UIOBJECT_H
#define GLES3JNI_UIOBJECT_H


#include "../Sprite.h"
#include "../Rectangle.h"

class UIObject {
public:
	UIObject(Sprite *sprite, glm::vec2 position = {0,0}, glm::vec2 size = {0,0});

	void setOnPress(std::function<void()> onPress);
	bool press(glm::vec2 position);

	inline Sprite* getSprite() { return sprite;}
	inline glm::vec2 getPosition() { return position; }
	inline glm::vec2 getSize() { return size; }
	inline Rectangle getRectangle() {
		return Rectangle(glm::vec2(position.x - size.x / 2, position.y - size.y /2), size);
	}

private:
	Sprite* sprite;
	glm::vec2 position;
	glm::vec2 size;
	std::function<void()> onPress;
};

#endif //GLES3JNI_UIOBJECT_H
