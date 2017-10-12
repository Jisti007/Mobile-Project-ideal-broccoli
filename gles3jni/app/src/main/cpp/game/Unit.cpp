#include "Unit.h"

Unit::Unit() {

}

Unit::Unit(uint16_t gridX, uint16_t gridY, UnitType *type) {
    initialize(gridX, gridY, type);
}

Unit::~Unit() {

}

void Unit::initialize(uint16_t gridX, uint16_t gridY, UnitType *type) {
    this->gridX = gridX;
    this->gridY = gridY;
    this->type = type;
}