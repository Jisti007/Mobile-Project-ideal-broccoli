//
// Created by K1697 on 20.10.2017.
//

#include "UIObject.h"
#include "../Rectangle.h"

UIObject::UIObject(Sprite *sprite, glm::vec2 position, glm::vec2 size) {
	this->sprite = sprite;
	this->position = position;
	this->size = size;
}

void UIObject::setOnPress(std::function<void()> onPress) {
	this->onPress = onPress;
}

bool UIObject::press(glm::vec2 position) {
	if (getRectangle().contains(position)) {
		onPress();
		return true;
	}
	return false;
}
