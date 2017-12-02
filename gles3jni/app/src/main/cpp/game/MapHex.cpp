#include "MapHex.h"
#include "pathing/MovementLink.h"

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
	return getDistance(destinationHex);
}

std::vector<MapHex*> MapHex::getHexesWithin(int radius, GameMap* map) {
	std::vector<MapHex*> hexes;

	int minX = getGridX() - radius;
	int minY = getGridY() - radius;
	int maxX = getGridX() + radius;
	int maxY = getGridY() + radius;

	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			auto hex = map->tryGetHex(x, y);
			if (hex != nullptr && getDistance(hex) <= radius) {
				hexes.push_back(hex);
			}
		}
	}

	return hexes;
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

int MapHex::getDistance(MapHex* other) {
	Point3D cube = getCubePosition();
	Point3D otherCube = other->getCubePosition();
	return (
		abs(cube.x - otherCube.x)
		+ abs(cube.y - otherCube.y)
		+ abs(cube.z - otherCube.z)
	) / 2;
}

Point3D MapHex::getCubePosition() {
	int x = gridX;
	int z = gridY - (gridX + (gridX & 1)) / 2;
	int y = -x - z;
	return Point3D{x, y, z};
}
