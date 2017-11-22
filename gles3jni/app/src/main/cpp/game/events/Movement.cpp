#include "Movement.h"
#include "../scenes/MovementAnimation.h"

Movement::Movement(Unit* unit, std::list<Link*> path) {
	this->unit = unit;
	this->path = path;
}

Movement::~Movement() {

}

bool Movement::execute() {
	auto destinationHex = static_cast<MapHex*>(path.back()->getDestination());
	if (unit->moveTo(destinationHex)) {
		auto scene = unit->getMap()->getScene();
		for (auto& link : path) {
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
	auto sourceHex = static_cast<MapHex*>(path.front()->getSource());
	if (unit->moveTo(sourceHex)) {
		unit->getActor()->setPosition(sourceHex->getActor()->getPosition());
		return true;
	}
	return false;
}
