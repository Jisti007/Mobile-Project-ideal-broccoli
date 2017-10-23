#include "GameMap.h"
#include "Rectangle.h"

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
				mapObjects.push_back(std::unique_ptr<Unit>(new Unit(x, y, testUnit)));
			}
		}
	}

	BuildingType* testBuilding = assets->getBuildingType("test");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto rn = rand() % 100;
			if (rn > 95) {
				mapObjects.push_back(std::unique_ptr<Building>(new Building(x, y, testBuilding)));
			}
		}
	}
}

void GameMap::draw() {
	pipeline->beginRender(camera.getPosition(), camera.getSize());

	for (auto& hex : hexes) {
		auto position = getScreenPosition(hex.getGridX(), hex.getGridY());
		if (camera.getBounds().contains(position)) {
			pipeline->render(hex.getSprite(), position);
		}
	}

	for (auto& mapObject : mapObjects) {
		auto position = getScreenPosition(mapObject->getGridX(), mapObject->getGridY());
		if (camera.getBounds().contains(position)) {
			pipeline->render(mapObject->getSprite(), position);
		}
	}

	pipeline->endRender();
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
		hex.getType().;
	}
}
