#ifndef GLES3JNI_CAMERA_H
#define GLES3JNI_CAMERA_H

#include "../glm/vec2.hpp"

class Camera {
public:
	Camera();
	~Camera();

	void move(glm::vec2 position);
	void moveBy(glm::vec2 delta);

	glm::vec2 getSize() {return {zoom * size.x, zoom * size.y};}
	float getX() {return position.x;}
	float getY() {return position.y;}
	void setSize(glm::vec2 size) {this->size = size;}

private:
	glm::vec2 position;
	glm::vec2 size;
	float zoom = 0.5f;
};

#endif //GLES3JNI_CAMERA_H
