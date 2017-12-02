#include "UIObject.h"

UIObject::UIObject(glm::vec2 position, glm::vec2 size) {
	this->position = position;
	this->size = size;
}

void UIObject::draw(Pipeline *pipeline) {
	onDraw(pipeline);
	for (auto& child : children) {
		child->draw(pipeline);
	}
}

void UIObject::setOnPress(std::function<void(void*)> onPress) {
	this->onPress = onPress;
}

bool UIObject::press(glm::vec2 position) {
	for (auto& child : children) {
		if (child->press(position)) {
			return true;
		}
	}
	if (getRectangle().contains(position)) {
		if (onPress) {
			onPress(onPressArgs);
		}
		return true;
	}
	return false;
}

void UIObject::addChild(std::unique_ptr<UIObject>& newChild) {
	children.push_back(std::move(newChild));
}

