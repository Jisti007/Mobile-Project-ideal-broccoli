#include "Movement.h"

Movement::Movement(Unit* unit, std::list<Link*> path) {
	this->unit = unit;
	this->path = path;
}

Movement::~Movement() {

}

void Movement::beginAnimation() {
	animationPath = path;
}

bool Movement::animate(float deltaTime) {
	auto nextHex = static_cast<MapHex*>(animationPath.front()->getDestination());
	auto hexPosition = nextHex->getPosition();
	auto deltaPosition = hexPosition - unit->getPosition();
	auto distanceSquared = glm::dot(deltaPosition, deltaPosition);
	const auto movementSpeed = 2.0f;
	auto movementDistance = movementSpeed * deltaTime;
	if (distanceSquared <= movementDistance * movementDistance) {
		unit->setPosition(hexPosition);
		animationPath.pop_front();
	} else {
		auto direction = glm::normalize(deltaPosition);
		unit->moveBy(direction * movementDistance);
	}

	return animationPath.size() == 0;
}

void Movement::endAnimation() {

}

bool Movement::execute() {
	auto destinationHex = static_cast<MapHex*>(path.back()->getDestination());
	return unit->moveTo(destinationHex);
}

bool Movement::cancel() {
	auto sourceHex = static_cast<MapHex*>(path.front()->getSource());
	return unit->moveTo(sourceHex);
}
