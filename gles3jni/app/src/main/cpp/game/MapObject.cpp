#include "MapObject.h"

MapObject::MapObject(uint16_t gridX, uint16_t gridY, glm::vec2 position) {
	this->gridX = gridX;
	this->gridY = gridY;
	this->position = position;
}

MapObject::~MapObject() {

}
