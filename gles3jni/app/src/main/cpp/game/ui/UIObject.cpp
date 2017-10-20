//
// Created by K1697 on 20.10.2017.
//

#include "UIObject.h"

UIObject::UIObject(Sprite *sprite, glm::vec2 position, glm::vec2 size) {
	this->sprite = sprite;
	this->position = position;
	this->size = size;
}
