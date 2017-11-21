#include "MovementAnimation.h"
#include "../GameMap.h"

MovementAnimation::MovementAnimation(Actor* actor, glm::vec2 destination) {
	this->actor = actor;
	this->destination = destination;
}

bool MovementAnimation::animate(float deltaTime) {
	auto deltaPosition = destination - actor->getPosition();
	auto distanceSquared = glm::dot(deltaPosition, deltaPosition);
	const auto movementSpeed = GameMap::gridSize * 2.0f;
	auto movementDistance = movementSpeed * deltaTime;
	if (distanceSquared <= movementDistance * movementDistance) {
		actor->setPosition(destination);
		return true;
	}

	auto direction = glm::normalize(deltaPosition);
	actor->offsetPosition(direction * movementDistance);
	return false;
}
