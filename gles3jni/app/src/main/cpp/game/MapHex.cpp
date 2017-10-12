#include "MapHex.h"

MapHex::MapHex() : MapObject(0,0) {

}

MapHex::MapHex(uint16_t gridX, uint16_t gridY, HexType *type) : MapObject(gridX, gridY) {
	this->type = type;
}

MapHex::~MapHex() {

}

void MapHex::initialize(uint16_t gridX, uint16_t gridY, HexType *type) {
	this->type = type;
	this->gridX = gridX;
	this->gridY = gridY;
}
