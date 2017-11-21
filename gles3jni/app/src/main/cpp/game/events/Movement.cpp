#include "Movement.h"

Movement::Movement(Unit* unit, std::list<Link*> path) {
	this->unit = unit;
	this->path = path;
}

Movement::~Movement() {

}

bool Movement::execute() {
	auto destinationHex = static_cast<MapHex*>(path.back()->getDestination());
	return unit->moveTo(destinationHex);
}

bool Movement::cancel() {
	auto sourceHex = static_cast<MapHex*>(path.front()->getSource());
	return unit->moveTo(sourceHex);
}
