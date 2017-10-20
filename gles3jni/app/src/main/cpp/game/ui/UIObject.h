//
// Created by K1697 on 20.10.2017.
//

#ifndef GLES3JNI_UIOBJECT_H
#define GLES3JNI_UIOBJECT_H


#include "../Sprite.h"

class UIObject {
public:
	UIObject(Sprite *sprite, glm::vec2 position = {0,0}, glm::vec2 size = {0,0});
	Sprite* getSprite() { return sprite;}
	glm::vec2 getPosition() { return position; }
	glm::vec2 getSize() { return size; }
	void setOnPress(std::function<void()> onPress);
	bool press(glm::vec2 position);
private:
	Sprite* sprite;
	glm::vec2 position;
	glm::vec2 size;
	std::function<void()> onPress;
};


#endif //GLES3JNI_UIOBJECT_H
