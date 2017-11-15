#ifndef GLES3JNI_RECTANGLE_H
#define GLES3JNI_RECTANGLE_H

#include "../glm/glm.hpp"

class Rectangle {
public:
	Rectangle(glm::vec2 position, glm::vec2 size);
	Rectangle(float left, float right, float top, float bottom);

	float left, right, top, bottom;

	bool contains(glm::vec2 position);
	bool overlaps(Rectangle other);

	inline float getLeft() { return left; }
	inline float getRight() { return right; }
	inline float getTop() { return top; }
	inline float getBottom() { return bottom; }
	inline glm::vec2 getTopLeft() { return {left, top}; }
	inline glm::vec2 getTopRight() { return {right, top}; }
	inline glm::vec2 getBottomLeft() { return {left, bottom}; }
	inline glm::vec2 getBottomRight() { return {right, bottom}; }
};

#endif //GLES3JNI_RECTANGLE_H
