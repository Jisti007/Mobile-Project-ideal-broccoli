#include "Unit.h"

Unit::Unit() {

}

Unit::Unit(uint16_t posX, uint16_t posY, UnitType *type) {
    initialize(posX, posY, type);
}

Unit::~Unit() {

}

void Unit::initialize(uint16_t posX, uint16_t posY, UnitType *type) {
    this->posX = posX;
    this->posY = posY;
    this->type = type;
}