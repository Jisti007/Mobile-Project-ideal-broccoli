#include "MovementAnimation.h"
#include "../GameMap.h"

MovementAnimation::MovementAnimation(Actor* actor, glm::vec2 destination, float speed, bool blocking)
	: Animation(blocking) {
	this->actor = actor;
	this->destination = destination;
	this->speed = speed;
}

bool MovementAnimation::onAnimate(float deltaTime) {
	auto deltaPosition = destination - actor->getPosition();
	auto distanceSquared = glm::dot(deltaPosition, deltaPosition);
	const auto movementSpeed = GameMap::gridSize * speed;
	auto movementDistance = movementSpeed * deltaTime;
	if (distanceSquared <= movementDistance * movementDistance) {
		actor->setPosition(destination);
		return true;
	}

	auto direction = glm::normalize(deltaPosition);
	actor->offsetPosition(direction * movementDistance);
	return false;
}
