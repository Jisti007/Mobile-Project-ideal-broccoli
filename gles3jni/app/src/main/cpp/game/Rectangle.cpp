//
// Created by K1697 on 20.10.2017.
//

#include "Rectangle.h"

bool Rectangle::contains(glm::vec2 position) {

	if(position.x < left) {
		return false;
	}
	if(position.x > right) {
		return false;
	}
	if(position.y < bottom) {
		return false;
	}
	if(position.y > top) {
		return false;
	}
	return true;
}

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
