#include "Building.h"

Building::Building() : MapObject(0,0) {}

Building::Building(uint16_t gridX, uint16_t gridY, BuildingType *type) : MapObject(gridX, gridY) {
	this->type = type;
}

Building::~Building() {}
