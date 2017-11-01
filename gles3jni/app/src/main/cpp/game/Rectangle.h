#ifndef GLES3JNI_RECTANGLE_H
#define GLES3JNI_RECTANGLE_H

#include "../glm/glm.hpp"

class Rectangle {
public:
	Rectangle(glm::vec2 position, glm::vec2 size);
	Rectangle(float left, float right, float top, float bottom);
	float left, right, top, bottom;
	bool contains(glm::vec2 position);
};


#endif //GLES3JNI_RECTANGLE_H
