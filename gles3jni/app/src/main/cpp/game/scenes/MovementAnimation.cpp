#include "MovementAnimation.h"
#include "../GameMap.h"

MovementAnimation::MovementAnimation(
	Actor* actor, Scene* scene, glm::vec2 destination,
	bool follows, float speed, bool blocking
) : Animation(blocking) {
	this->actor = actor;
	this->scene = scene;
	this->destination = destination;
	this->follows = follows;
	this->speed = speed;
}

bool MovementAnimation::onAnimate(float deltaTime) {
	auto deltaPosition = destination - actor->getPosition();
	auto distanceSquared = glm::dot(deltaPosition, deltaPosition);
	const auto movementSpeed = GameMap::gridSize * speed;
	auto movementDistance = movementSpeed * deltaTime;
	bool destinationReached = false;
	if (distanceSquared <= movementDistance * movementDistance) {
		actor->setPosition(destination);
		destinationReached = true;
	} else {
		auto direction = glm::normalize(deltaPosition);
		actor->offsetPosition(direction * movementDistance);
	}
	if (follows) {
		scene->getCamera()->move(actor->getPosition() / 128.0f);
	}
	return destinationReached;
}
