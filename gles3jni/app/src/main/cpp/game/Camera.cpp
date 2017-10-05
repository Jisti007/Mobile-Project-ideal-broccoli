#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::move(glm::vec2 position) {
	this->position = position;
}

void Camera::moveBy(glm::vec2 delta) {
	position += delta;
}
