#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::setZoom(float zoom) {
	if (zoom < minZoom) {
		zoom = minZoom;
	} else if (zoom > maxZoom) {
		zoom = maxZoom;
	}
	this->zoom = zoom;
}

void Camera::update(float deltaTime) {
	velocity = getTarget() - getPosition();
	moveBy(10.0f * deltaTime * velocity);
}

void Camera::move(glm::vec2 position) {
	if (position.x < minPosition.x) {
		position.x = minPosition.x;
	} else if (position.x > maxPosition.x) {
		position.x = maxPosition.x;
	}
	if (position.y < minPosition.y) {
		position.y = minPosition.y;
	} else if (position.y > maxPosition.y) {
		position.y = maxPosition.y;
	}

	this->position = position;
}

void Camera::moveBy(glm::vec2 delta) {
	move(position + delta);
}
