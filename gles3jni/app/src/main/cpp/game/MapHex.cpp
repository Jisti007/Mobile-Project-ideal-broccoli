#include "MapHex.h"
#include "pathing/MovementLink.h"
#include "Random.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "../glm/gtx/rotate_vector.hpp"

MapHex::MapHex(uint16_t gridX, uint16_t gridY, HexType* type, GameMap* map)
	: MapObject(gridX, gridY) {
	this->type = type;
	this->unit = nullptr;
	this->region = nullptr;
	this->map = map;
}

MapHex::~MapHex() {

}

float MapHex::getHeuristic(Node* destination) {
	auto destinationHex = static_cast<MapHex*>(destination);
	return getDistance(destinationHex);
}

std::vector<MapHex*> MapHex::getHexesWithin(int radius) {
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

void MapHex::initializeNeighbors() {
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

void MapHex::setRegion(MapRegion* region) {
	this->region = region;
	if (region != nullptr) {
		type = region->getBiome()->getRandomHexType();
	}
}

void MapHex::clearDecorations() {
	auto scene = map->getScene();
	for (auto& decoration : decorations) {
		scene->removeActor(decoration);
	}
	decorations.clear();
}

void MapHex::createDecorations() {
	auto scene = map->getScene();
	for (auto& decorationSprite : getType()->getRandomDecorations()) {
		auto offset = glm::vec2(Random::generateFloat() * type->getDecorationDistance(), 0);
		auto angle = 360.0f * Random::generateFloat();
		offset = glm::rotate(offset, angle);
		auto position = map->getHexPosition(getGridX(), getGridY()) + offset;
		position = map->getScreenPosition(position);
		auto decorationActor = scene->addNew<Actor>(decorationSprite, position, -position.y, DECORATION_LAYER);
		decorations.push_back(decorationActor);
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
