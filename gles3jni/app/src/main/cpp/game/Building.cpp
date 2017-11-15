#include "Building.h"

Building::Building(uint16_t gridX, uint16_t gridY, glm::vec2 position, BuildingType *type)
	: MapObject(gridX, gridY, position) {
	this->type = type;
}

Building::~Building() {}
