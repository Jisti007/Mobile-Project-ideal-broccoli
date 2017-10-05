#ifndef GLES3JNI_CAMERA_H
#define GLES3JNI_CAMERA_H

#include "../glm/vec2.hpp"

class Camera {
public:
	Camera();
	~Camera();

	void move(glm::vec2 position);
	void moveBy(glm::vec2 delta);

private:
	glm::vec2 position;
};

#endif //GLES3JNI_CAMERA_H
