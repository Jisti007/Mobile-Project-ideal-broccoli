#include "GameMap.h"

GameMap::GameMap() {

}

GameMap::GameMap(uint16_t width, uint16_t height, AssetManager* assets) {
	initialize(width, height, assets, nullptr);
}

GameMap::~GameMap() {

}

void GameMap::initialize(uint16_t width, uint16_t height, AssetManager* assets, Pipeline* pipeline) {
	this->width = width;
	this->height = height;
	this->pipeline = pipeline;
	this->assets = assets;
	hexes.resize(width * height);

	generate();
}

void GameMap::generate() {
	mapObjects.clear();
	HexType* grass = assets->getHexType("grass");
	HexType* sand = assets->getHexType("sand");
	HexType* water = assets->getHexType("water");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto rn = rand() % 100;
			if (rn > 70) {
				getHex(x, y)->initialize(x, y, grass);
			}
			else if (rn > 50) {
				getHex(x, y)->initialize(x, y, sand);
			}
			else {
				getHex(x, y)->initialize(x, y, water);
			}
		}
	}

	UnitType* test_unit = assets->getUnitType("test");

	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto rn = rand() % 100;
			if (rn > 95) {
				mapObjects.push_back(std::unique_ptr<Unit>(new Unit(x, y, test_unit)));
			}
		}
	}

	BuildingType* test_building = assets->getBuildingType("test");

	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto rn = rand() % 100;
			if (rn > 95) {
				mapObjects.push_back(std::unique_ptr<Building>(new Building(x, y, test_building)));
			}
		}
	}
}

void GameMap::draw() {
	pipeline->beginRender(camera.getPosition(), camera.getSize());

	for (auto& hex : hexes) {
		auto position = getScreenPosition(hex.getGridX(), hex.getGridY());
		if (
			position.x + camera.getX() < -camera.getSize().x
			|| position.x + camera.getX() > camera.getSize().x
			|| position.y + camera.getY() < -camera.getSize().y
			|| position.y + camera.getY() > camera.getSize().y
			) {
			continue;
		}

		pipeline->render(hex.getSprite(), position);
	}

	for (auto&& mapObject : mapObjects) {
		auto position = getScreenPosition(mapObject->getGridX(), mapObject->getGridY());
		if (
			position.x + camera.getX() < -camera.getSize().x
			|| position.x + camera.getX() > camera.getSize().x
			|| position.y + camera.getY() < -camera.getSize().y
			|| position.y + camera.getY() > camera.getSize().y
			) {
			continue;
		}

		pipeline->render(mapObject->getSprite(), position);
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
	} else {
		position = {xOffset * x, y};
	}

	position.x *= gridSize;
	position.y *= gridSize;

	return position;
}