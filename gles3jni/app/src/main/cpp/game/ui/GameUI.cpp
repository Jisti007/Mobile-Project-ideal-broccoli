//
// Created by K1697 on 20.10.2017.
//

#include "GameUI.h"

void GameUI::Add(std::shared_ptr<UIObject> object) {
	uiObjects.push_back(object);
}

void GameUI::draw(Pipeline *pipeline) {
	pipeline->beginDraw({0, 0}, {960, 540});

	for (auto& uiObject : uiObjects) {
		pipeline->draw(uiObject->getSprite(), uiObject->getPosition());
	}

	pipeline->endDraw();
}

void GameUI::press(glm::vec2 position) {
	for (auto& uiObject : uiObjects) {
		if(uiObject->press(position)) {
			break;
		}
	}
}

void GameUI::clear() {
	uiObjects.clear();
}



