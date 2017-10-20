//
// Created by K1697 on 20.10.2017.
//

#ifndef GLES3JNI_GAMEUI_H
#define GLES3JNI_GAMEUI_H


#include <vector>
#include "../../glm/vec2.hpp"
#include "UIObject.h"
#include "../Pipeline.h"

class GameUI {
public:
	void Add(std::shared_ptr<UIObject> object);
	void draw(Pipeline *pipeline);
	void press(glm::vec2 position);
private:
	std::vector<std::shared_ptr<UIObject>> uiObjects;
};


#endif //GLES3JNI_GAMEUI_H
