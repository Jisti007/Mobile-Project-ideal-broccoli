#include "Building.h"

Building::Building(uint16_t gridX, uint16_t gridY, glm::vec2 position, BuildingType *type, Faction* faction)
	: MapObject(gridX, gridY, position) {
	this->type = type;
	this->faction = faction;
}

Building::~Building() {}
