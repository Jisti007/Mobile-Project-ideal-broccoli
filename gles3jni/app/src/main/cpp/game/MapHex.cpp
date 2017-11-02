#include "MapHex.h"

MapHex::MapHex() : MapObject(0,0) {

}

MapHex::MapHex(uint16_t gridX, uint16_t gridY, HexType* type)
	: MapObject(gridX, gridY) {
	this->type = type;
	this->unit = nullptr;
	this->region = nullptr;
}

MapHex::~MapHex() {

}

float MapHex::getHeuristic(Node* destination) {
	auto destinationHex = static_cast<MapHex*>(destination);
	int dx = destinationHex->getGridX() - getGridX();
	int dy = destinationHex->getGridY() - getGridY();
	return abs(dx) + abs(dy);
}
/*
void MapHex::initialize(uint16_t gridX, uint16_t gridY, HexType* type) {
	this->type = type;
	this->gridX = gridX;
	this->gridY = gridY;
	this->unit = nullptr;
	this->region = nullptr;
}
*/
void MapHex::initializeNeighbors(GameMap* map) {
	neighbors.clear();
	neighbors.reserve(6);
	//links.clear();
	//links.reserve(6);

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
		MapHex* neighbor = map->getHex((uint16_t)x, (uint16_t)y);
		neighbors.push_back(neighbor);

		//TODO: Switch to C++14 and use std::make_unique.
		auto link = std::unique_ptr<Link>(new SimpleLink(
			this, neighbor, neighbor->type->getMovementCost()
		));
		links.push_back(std::move(link));
	}
}

void MapHex::updateType() {
	type = region->getBiome()->getRandomHexType();
}
