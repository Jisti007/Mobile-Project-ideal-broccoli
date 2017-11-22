#include "MovementLink.h"

MovementLink::MovementLink(MapHex* source, MapHex* destination) : Link(source, destination) {

}

float MovementLink::getCost(Agent* agent, float pathCost) {
	auto destinationHex = static_cast<MapHex*>(destination);
	auto destinationUnit = destinationHex->getUnit();
	if (destinationUnit != nullptr) {
		auto unit = static_cast<Unit*>(agent);
		if (unit->getFaction() != destinationUnit->getFaction()) {
			return 1000.0f;
		}
	}

	return destinationHex->getType()->getMovementCost();
}
