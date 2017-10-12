#include "Building.h"

Building::Building() {}

Building::Building(uint16_t posX, uint16_t posY, BuildingType *type) {
	initialize(posX, posY, type);
}

Building::~Building() {}

void Building::initialize(uint16_t posX, uint16_t posY, BuildingType *type) {
	this->posX = posX;
	this->posY = posY;
	this->type = type;
}