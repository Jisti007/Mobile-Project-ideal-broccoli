#ifndef GLES3JNI_CAMERA_H
#define GLES3JNI_CAMERA_H

#include "../glm/glm.hpp"
#include "Rectangle.h"

class Camera {
public:
	Camera();
	~Camera();

	void move(glm::vec2 position);
	void moveBy(glm::vec2 delta);

	inline glm::vec2 getPosition() { return position; }
	inline glm::vec2 getSize() { return {getWidth(), getHeight()}; }
	inline void setSize(glm::vec2 size) { this->size = size; }
	inline float getX() { return position.x; }
	inline float getY() { return position.y; }
	inline float getWidth() { return zoom * size.x; }
	inline float getHeight() { return zoom * size.y; }
	inline Rectangle getBounds() {
		return Rectangle(
			getX() - getWidth(),
			getX() + getWidth(),
			getY() + getHeight(),
			getY() - getHeight()
		);
	}

private:
	glm::vec2 position;
	glm::vec2 size;
	float zoom = 0.5f;
};

#endif //GLES3JNI_CAMERA_H
