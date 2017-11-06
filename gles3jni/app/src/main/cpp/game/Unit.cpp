#include "Unit.h"

Unit::Unit() : MapObject(0, 0) {

}

Unit::Unit(uint16_t gridX, uint16_t gridY, UnitType *type, Faction* faction, GameMap* map)
	: MapObject(gridX, gridY) {
	this->type = type;
	this->faction = faction;
	this->map = map;
}

Unit::~Unit() {

}

void Unit::moveTo(MapHex* destination) {
	if (destination->getUnit() != nullptr) {
		return;
	}

	MapHex* origin = map->tryGetHex(getGridX(), getGridY());
	if (origin == nullptr) {
		return;
	}

	if (origin->getUnit() == this) {
		origin->setUnit(nullptr);
	}

	destination->setUnit(this);
	gridX = destination->getGridX();
	gridY = destination->getGridY();
}
