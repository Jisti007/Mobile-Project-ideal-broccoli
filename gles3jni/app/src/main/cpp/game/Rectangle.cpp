//
// Created by K1697 on 20.10.2017.
//

#include "Rectangle.h"

Rectangle::Rectangle(glm::vec2 position, glm::vec2 size) {
	left = position.x;
	bottom = position.y;
	right = left + size.x;
	top = bottom + size.y;
}

Rectangle::Rectangle(float left, float right, float top, float bottom) {
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

bool Rectangle::contains(glm::vec2 position) {
	return
		position.x >= left
		&& position.x <= right
		&& position.y >= bottom
		&& position.y <= top;
}
