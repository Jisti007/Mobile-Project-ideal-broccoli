#include "MapHex.h"
#include "GameMap.h"

MapHex::MapHex() : MapObject(0,0) {

}

MapHex::MapHex(uint16_t gridX, uint16_t gridY, HexType* type, GameMap* map)
	: MapObject(gridX, gridY) {
	this->type = type;
}

MapHex::~MapHex() {

}

void MapHex::initialize(uint16_t gridX, uint16_t gridY, HexType* type, GameMap* map) {
	this->type = type;
	this->gridX = gridX;
	this->gridY = gridY;

	addNeighbor(map, gridX, gridY + 1);
	addNeighbor(map, gridX, gridY - 1);
	addNeighbor(map, gridX + 1, gridY);
	addNeighbor(map, gridX - 1, gridY);
	if (gridX % 2) {
		addNeighbor(map, gridX + 1, gridY - 1);
		addNeighbor(map, gridX - 1, gridY - 1);
	}
	else {
		addNeighbor(map, gridX + 1, gridY + 1);
		addNeighbor(map, gridX - 1, gridY + 1);
	}
}

void MapHex::addNeighbor(GameMap* map, int x, int y) {
	if (x >= 0 && x < map->getWidth() && y >= 0 && y < map->getHeight()) {
		neighbors.push_back(map->getHex((uint16_t)x, (uint16_t)y));
	}
}
