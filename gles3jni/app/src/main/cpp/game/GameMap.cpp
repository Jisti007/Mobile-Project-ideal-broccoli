#include "GameMap.h"

using namespace std;

const float gridSize = 128;
const float xOffset = 0.75;
const float yOffset = 0.50;

GameMap::GameMap() {

}

GameMap::GameMap(uint16_t width, uint16_t height, Scenario* scenario) {
	initialize(width, height, scenario);
}

GameMap::~GameMap() {

}

void GameMap::initialize(uint16_t width, uint16_t height, Scenario* scenario) {
	this->width = width;
	this->height = height;
	this->scenario = scenario;
	//this->pipeline = pipeline;
	//this->assets = assets;
	/*
	vector<glm::vec3> testFaction1Colors = {{1, 0, 0}, {0, 1, 1}};
	vector<glm::vec3> testFaction2Colors = {{0, 1, 0}, {1, 0, 1}};
	vector<glm::vec3> testFaction3Colors = {{0, 0, 1}, {1, 1, 0}};
	Faction testFaction1(testFaction1Colors);
	Faction testFaction2(testFaction2Colors);
	Faction testFaction3(testFaction3Colors);
	factions.push_back(testFaction1);
	factions.push_back(testFaction2);
	factions.push_back(testFaction3);
	*/
	initializeHexes();
	generate();
}

void GameMap::generate() {
	regions.clear();
	expanders.clear();
	mapObjects.clear();
	units.clear();

	initializeRegions(100);
	expandRegions(-1, -1);

	auto assets = scenario->getCampaign()->getGame()->getAssets();
	HexType* water = assets->getHexType("water");
	UnitType* testUnit = assets->getUnitType("test");
	BuildingType* testBuilding = assets->getBuildingType("test");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			if (getHex(x, y)->getType() != water) {
				glm::vec2 hexPosition = getHexPosition(x, y);

				auto rn = rand() % 100;
				if (rn > 95) {
					auto faction = scenario->getFaction(rand() % scenario->getFactionCount());
					createUnit({x, y}, testUnit, faction);
				}

				rn = rand() % 100;
				if (rn > 95) {
					mapObjects.push_back(make_unique<Building>(x, y, hexPosition, testBuilding));
				}
			}
		}
	}
}

void GameMap::draw() {
	auto pipeline = scenario->getCampaign()->getGame()->getPipeline();
	pipeline->beginDraw();
	pipeline->setCameraPosition(camera.getPosition());

	for (auto& hex : hexes) {
		auto position = getScreenPosition(hex->getPosition());
		pipeline->draw(hex->getSprite(), position);
	}

	for (auto& mapObject : mapObjects) {
		auto position = getScreenPosition(mapObject->getPosition());
		pipeline->draw(mapObject->getSprite(), position);
	}

	for (auto& unit : units) {
		auto position = getScreenPosition(unit->getPosition());
		pipeline->draw(unit->getSprite(), position, unit->getFaction()->getColors());
	}

	pipeline->endDraw();
}

Unit* GameMap::createUnit(Point position, UnitType* type, Faction* faction) {
	MapHex* hex = tryGetHex(position);
	if (hex == nullptr || hex->getUnit() != nullptr) {
		return nullptr;
	}

	auto unit = new Unit(hex->getGridX(), hex->getGridY(), hex->getPosition(), type, faction, this);
	units.push_back(std::unique_ptr<Unit>(unit));
	hex->setUnit(unit);
	return unit;
}

MapHex* GameMap::tryGetHex(int x, int y) {
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return nullptr;
	}
	return getHex(x, y);
}

Point GameMap::getGridPosition(glm::vec2 screenPosition) {
	//TODO: Android Studio complains about this, but it builds fine. Find a way to silence it?
	auto position = screenPosition + camera.getPosition();
	position.x /= gridSize * xOffset;
	position.y /= gridSize;

	int minX = (int)position.x;
	int minY = (int)position.y;
	int maxX = minX + 1;
	int maxY = minY + 1;

	Point nearest{0, 0};
	float nearestDistanceSquared = numeric_limits<float>::max();
	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			auto hexPosition = getHexPosition(x, y);
			auto delta = hexPosition - position;
			auto distanceSquared = glm::dot(delta, delta);
			if (distanceSquared < nearestDistanceSquared) {
				nearest = Point{x, y};
				nearestDistanceSquared = distanceSquared;
			}
		}
	}

	return nearest;
}

glm::vec2 GameMap::getHexPosition(int x, int y) {
	glm::vec2 position = {x, y};

	if (x % 2) {
		position = {xOffset * x, y - yOffset};
	}
	else {
		position = {xOffset * x, y};
	}

	return position;
}

void GameMap::initializeHexes() {
	hexes.clear();
	hexes.reserve(width * height);

	auto assets = scenario->getCampaign()->getGame()->getAssets();
	HexType* grass = assets->getHexType("grass");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto position = getHexPosition(x, y);
			auto hex = make_unique<MapHex>(x, y, position, grass);
			hexes.push_back(move(hex));
		}
	}

	for (auto& hex : hexes) {
		hex->initializeNeighbors(this);
	}
}

void GameMap::initializeRegions(int count) {
	regions.clear();
	expanders.clear();
	regions.reserve((size_t)count);
	expanders.reserve((size_t)count);

	for (auto& hex : hexes) {
		hex->setRegion(nullptr);
	}

	auto assets = scenario->getCampaign()->getGame()->getAssets();
	for (int i = 0; i < count; i++) {
		auto regionOrigin = findFreeHex(100);
		if (!regionOrigin) {
			continue;
		}

		regions.emplace_back(assets->getRandomBiome());
		auto region = &regions.back();
		expanders.push_back(region);
		region->expandTo(regionOrigin);
		for (int j = 0; j < 10; j++) {
			if (!region->expandRandom()) {
				break;
			}
		}
	}
}

void GameMap::expandRegions(int iterations, int maxPerRegion) {
	if (maxPerRegion <= 0) {
		maxPerRegion = getDefaultMaxExpansionsPerRegion();
	}

	while (iterations != 0 && expanders.size() > 0) {
		int regionIndex = rand() % (int)expanders.size();
		auto region = expanders[regionIndex];
		int n = rand() % maxPerRegion;
		if (iterations >= 0 && n > iterations) {
			n = iterations;
		}

		for (int i = 0; i < n; i++) {
			if (!region->expandRandom()) {
				expanders.erase(expanders.begin() + regionIndex);
				break;
			}
			iterations--;
		}
	}
}

MapHex* GameMap::findFreeHex(int maxTries) {
	while (maxTries) {
		uint16_t x = (uint16_t)(rand() % width);
		uint16_t y = (uint16_t)(rand() % height);
		auto hex = getHex(x, y);
		if (hex->getRegion() == nullptr) {
			return hex;
		}

		maxTries--;
	}

	return nullptr;
}

glm::vec2 GameMap::getScreenPosition(int32_t x, int32_t y) {
	glm::vec2 hexPosition = getHexPosition(x, y);
	return getScreenPosition(hexPosition);
}

glm::vec2 GameMap::getScreenPosition(glm::vec2 hexPosition) {
	return gridSize * hexPosition;
}

