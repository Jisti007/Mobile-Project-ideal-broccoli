#include "Building.h"

Building::Building(uint16_t gridX, uint16_t gridY, BuildingType *type, Faction* faction)
	: MapObject(gridX, gridY) {
	this->type = type;
	this->faction = faction;
}

Building::~Building() {}
