#include "Movement.h"
#include "../scenes/MovementAnimation.h"

Movement::Movement(Unit* unit, Path path) : path(path) {
	this->unit = unit;
}

Movement::~Movement() {

}

bool Movement::execute() {
	return unit->move(path);
}

bool Movement::cancel() {
	auto sourceHex = static_cast<MapHex*>(path.getLinks().front()->getSource());
	if (unit->moveTo(sourceHex)) {
		unit->getActor()->setPosition(sourceHex->getActor()->getPosition());
		return true;
	}
	return false;
}
