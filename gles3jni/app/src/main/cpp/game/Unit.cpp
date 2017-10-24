#include "Unit.h"

Unit::Unit() : MapObject(0, 0) {

}

Unit::Unit(uint16_t gridX, uint16_t gridY, UnitType *type, Faction* faction) : MapObject(gridX, gridY) {
	this->type = type;
	this->faction = faction;
}

Unit::~Unit() {

}