#ifndef GLES3JNI_CAMERA_H
#define GLES3JNI_CAMERA_H

#include "../glm/vec2.hpp"

class Camera {
public:
	Camera();
	~Camera();

	void move(glm::vec2 position);
	void moveBy(glm::vec2 delta);

	glm::vec2 getSize() {return size;}
	float getX() {return position.x;}
	float getY() {return position.y;}
	void setSize(glm::vec2 size) {this->size = size;}

private:
	glm::vec2 position;
	glm::vec2 size;
};

#endif //GLES3JNI_CAMERA_H
