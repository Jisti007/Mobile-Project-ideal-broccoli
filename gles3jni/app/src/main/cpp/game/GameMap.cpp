#include "GameMap.h"

using namespace std;

GameMap::GameMap() {

}

GameMap::GameMap(uint16_t width, uint16_t height, AssetManager* assets, Pipeline* pipeline) {
	initialize(width, height, assets, pipeline);
}

GameMap::~GameMap() {

}

void GameMap::initialize(uint16_t width, uint16_t height, AssetManager* assets, Pipeline* pipeline) {
	this->width = width;
	this->height = height;
	this->pipeline = pipeline;
	this->assets = assets;

	vector<glm::vec3> testFaction1Colors = {{255, 0, 0}};
	vector<glm::vec3> testFaction2Colors = {{0, 255, 0}};
	vector<glm::vec3> testFaction3Colors = {{0, 0, 255}};
	Faction testFaction1(testFaction1Colors);
	Faction testFaction2(testFaction2Colors);
	Faction testFaction3(testFaction3Colors);
	factions.push_back(testFaction1);
	factions.push_back(testFaction2);
	factions.push_back(testFaction3);

	generate();
}

void GameMap::generate() {
	regions.clear();
	expanders.clear();
	mapObjects.clear();

	initializeHexes();
	createRegions(100);
	expandRegions(-1, -1);
	updateHexTypes();

	UnitType* testUnit = assets->getUnitType("test");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto rn = rand() % 100;
			if (rn > 95) {
				auto faction = &factions[rand() % factions.size()];
				units.emplace_back(x, y, testUnit, faction);
				//mapObjects.push_back(unique_ptr<Unit>(new Unit(x, y, testUnit, faction)));
			}
		}
	}

	BuildingType* testBuilding = assets->getBuildingType("test");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto rn = rand() % 100;
			if (rn > 95) {
				mapObjects.push_back(unique_ptr<Building>(new Building(x, y, testBuilding)));
			}
		}
	}
}

void GameMap::draw() {
	pipeline->beginDraw(camera.getPosition(), camera.getSize());

	for (auto& hex : hexes) {
		auto position = getScreenPosition(hex.getGridX(), hex.getGridY());
		if (camera.getBounds().contains(position)) {
			pipeline->draw(hex.getSprite(), position);
		}
	}

	for (auto& mapObject : mapObjects) {
		auto position = getScreenPosition(mapObject->getGridX(), mapObject->getGridY());
		if (camera.getBounds().contains(position)) {
			pipeline->draw(mapObject->getSprite(), position);
		}
	}

	for (auto& unit : units) {
		auto position = getScreenPosition(unit.getGridX(), unit.getGridY());
		if (camera.getBounds().contains(position)) {
			pipeline->draw(unit.getSprite(), position, unit.getFaction()->getColors());
		}
	}

	pipeline->endDraw();
}

glm::vec2 GameMap::getScreenPosition(int32_t x, int32_t y) {
	glm::vec2 position = {x, y};

	const float gridSize = 128;

	float xOffset = 0.75;
	float yOffset = 0.50;

	if (x % 2) {
		position = {xOffset * x, y - yOffset};
	}
	else {
		position = {xOffset * x, y};
	}

	position.x *= gridSize;
	position.y *= gridSize;

	return position;
}

void GameMap::initializeHexes() {
	hexes.clear();
	hexes.resize(width * height);

	HexType* grass = assets->getHexType("grass");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto hex = getHex(x, y);
			hex->initialize(x, y, grass);
			hex->initializeNeighbors(this);
		}
	}
}

void GameMap::createRegions(int count) {
	regions.resize((size_t)count);
	expanders.resize((size_t)count);

	for (int i = 0; i < count; i++) {
		auto regionOrigin = findFreeHex(100);
		if (!regionOrigin) {
			continue;
		}

		regions[i] = MapRegion(assets->getRandomBiome());
		auto region = &regions[i];
		expanders[i] = region;
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

void GameMap::updateHexTypes() {
	for (auto& hex : hexes) {
		hex.updateType();
	}
}
