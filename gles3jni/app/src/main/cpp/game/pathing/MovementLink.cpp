#include "MovementLink.h"

MovementLink::MovementLink(MapHex* source, MapHex* destination) : Link(source, destination) {

}

float MovementLink::getCost(Agent* agent, float pathCost) {
	auto destinationHex = static_cast<MapHex*>(destination);
	return destinationHex->getType()->getMovementCost();
}
