#include "MapHex.h"
#include "pathing/MovementLink.h"

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
	/*
	auto destinationHex = static_cast<MapHex*>(destination);
	int dx = destinationHex->getGridX() - getGridX();
	int dy = destinationHex->getGridY() - getGridY();
	return abs(dx) + abs(dy);
	*/
	return 0;
}

void MapHex::initializeNeighbors(GameMap* map) {
	neighbors.clear();
	neighbors.reserve(6);
	links.clear();
	links.reserve(6);

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

		auto link = std::unique_ptr<Link>(new MovementLink(this, neighbor));
		links.push_back(std::move(link));
	}
}

void MapHex::setRegion(MapRegion* region) {
	this->region = region;
	if (region != nullptr) {
		type = region->getBiome()->getRandomHexType();
	}
}
