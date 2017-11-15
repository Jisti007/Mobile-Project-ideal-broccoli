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
	inline float getX() { return position.x; }
	inline float getY() { return position.y; }
	inline float getZoom() { return zoom; }

private:
	glm::vec2 position = {0, 0};
	float zoom = 0.5f;
};

#endif //GLES3JNI_CAMERA_H
