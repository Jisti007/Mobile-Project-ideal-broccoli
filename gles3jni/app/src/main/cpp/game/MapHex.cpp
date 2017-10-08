#include "MapHex.h"

MapHex::MapHex() {

}

MapHex::MapHex(uint16_t gridX, uint16_t gridY, HexType *type) {
	initialize(gridX, gridY, type);
}

MapHex::~MapHex() {

}

void MapHex::initialize(uint16_t gridX, uint16_t gridY, HexType *type) {
	this->gridX = gridX;
	this->gridY = gridY;
	this->type = type;
}
