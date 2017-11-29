#include "Movement.h"
#include "../scenes/MovementAnimation.h"

Movement::Movement(Unit* unit, Path path) : path(path) {
	this->unit = unit;
}

Movement::~Movement() {

}

bool Movement::execute() {
	auto destinationHex = static_cast<MapHex*>(path.getLinks().back()->getDestination());
	if (unit->moveTo(destinationHex)) {
		unit->modifyMovement(-path.getCost());
		auto scene = unit->getMap()->getScene();
		for (auto& link : path.getLinks()) {
			auto linkDestinationHex = static_cast<MapHex*>(link->getDestination());
			auto animation = std::unique_ptr<Animation>(new MovementAnimation(
				unit->getActor(), linkDestinationHex->getActor()->getPosition()
			));
			scene->queueAnimation(animation);
		}
		return true;
	}
	return false;
}

bool Movement::cancel() {
	auto sourceHex = static_cast<MapHex*>(path.getLinks().front()->getSource());
	if (unit->moveTo(sourceHex)) {
		unit->getActor()->setPosition(sourceHex->getActor()->getPosition());
		return true;
	}
	return false;
}
