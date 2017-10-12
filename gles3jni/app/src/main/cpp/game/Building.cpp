#include "Building.h"

Building::Building() {}

Building::Building(uint16_t gridX, uint16_t gridY, BuildingType *type) {
	initialize(gridX, gridY, type);
}

Building::~Building() {}

void Building::initialize(uint16_t gridX, uint16_t gridY, BuildingType *type) {
	this->gridX = gridX;
	this->gridY = gridY;
	this->type = type;
}