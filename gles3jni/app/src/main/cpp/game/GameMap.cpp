#include "GameMap.h"
#include "scenes/RecoloredActor.h"
#include "Random.h"
#include <memory>

using namespace std;

const float GameMap::gridSize = 128.0f;
const float GameMap::xOffset = 0.75f;
const float GameMap::yOffset = 0.50f;

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
	camera.setZoom(2.0f);
	camera.setMaxPosition({width * xOffset, height});

	initializeHexes();
	generate();
}

void GameMap::generate() {
	regions.clear();
	expanders.clear();
	buildings.clear();
	units.clear();
	scene.clear();

	initializeRegions(100);
	expandRegions(-1, -1);

	auto assets = scenario->getCampaign()->getGame()->getAssets();
	HexType* water = assets->getHexType("water");
	UnitType* testUnit = assets->getUnitType("test");

	// TODO: Make a system for displaying all non-hardcoded resources the active player possesses.
	BuildingType* goldBuilding = assets->getBuildingType("gold");
	BuildingType* foodBuilding = assets->getBuildingType("food");
	BuildingType* materialBuilding = assets->getBuildingType("material");
	BuildingType* crystalBuilding = assets->getBuildingType("crystal");

	WeightedList<BuildingType*> buildingsList;
	buildingsList.add(goldBuilding, 15);
	buildingsList.add(foodBuilding, 15);
	buildingsList.add(materialBuilding, 10);
	buildingsList.add(crystalBuilding, 5);
	buildingsList.add(nullptr, 1000);

	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto hex = getHex(x, y);
			auto actor = createActor(
				hex->getSprite(), getHexPosition(x, y), -Random::generateFloat()
			);
			hex->setActor(actor);
			hex->clearDecorations();
			hex->createDecorations();

			if (hex->getType() != water) {
				auto rn = rand() % 100;
				if (rn > 95) {
					auto faction = scenario->getFaction(rand() % scenario->getFactionCount());
					createUnit({x, y}, testUnit, faction);
				}

				auto buildingType = buildingsList.getRandom();
				if (buildingType != nullptr) {
					auto faction = scenario->getFaction(rand() % scenario->getFactionCount());
					createBuilding({x, y}, buildingType, faction);
				}
			}
		}
	}
}

void GameMap::draw(float deltaTime) {
	auto pipeline = scenario->getCampaign()->getGame()->getPipeline();
	pipeline->setCameraPosition(camera.getPosition() * gridSize);
	pipeline->setCameraZoom(camera.getZoom());
	scene.draw(pipeline, deltaTime);
	/*
	auto debugMarker = scenario->getCampaign()->getGame()->getAssets()->getSprite("dot_marker");
	pipeline->draw(debugMarker, debugPosition, 1.0f);
	*/
}

void GameMap::onBeginTurn() {
	for (auto& unit : units) {
		unit->onBeginTurn();
	}
	for (auto& building : buildings) {
		building->onBeginTurn(this);
	}
}

Unit* GameMap::createUnit(Point position, UnitType* type, Faction* faction) {
	MapHex* hex = tryGetHex(position);
	if (hex == nullptr || hex->getUnit() != nullptr) {
		return nullptr;
	}

	auto x = position.x;
	auto y = position.y;
	auto actor = createActor(type->getSprite(), getHexPosition(x, y), faction->getColors(), 1.0f);
	auto unit = new Unit(
		hex->getGridX(), hex->getGridY(), type, faction, this
	);
	unit->setActor(actor);
	units.push_back(std::unique_ptr<Unit>(unit));
	hex->setUnit(unit);
	return unit;
}

void GameMap::removeUnit(Unit* unit) {
	auto unitHex = getHex(unit->getGridX(), unit->getGridY());
	unitHex->setUnit(nullptr);
	for (int i = 0; i < units.size(); i++) {
		if (units[i].get() == unit) {
			units.erase(units.begin() + i);
			break;
		}
	}
}

Building* GameMap::createBuilding(Point position, BuildingType* type, Faction* faction) {
	MapHex* hex = tryGetHex(position);
	if (hex == nullptr || hex->getUnit() != nullptr) {
		return nullptr;
	}

	auto x = position.x;
	auto y = position.y;
	auto actor = createActor(type->getSprite(), getHexPosition(x, y), faction->getColors(), 0.5f);
	auto building = new Building(
		hex->getGridX(), hex->getGridY(), type, faction
	);
	building->setActor(actor);
	buildings.push_back(std::unique_ptr<Building>(building));
	hex->setBuilding(building);
	return building;
}

MapHex* GameMap::tryGetHex(int x, int y) {
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return nullptr;
	}
	return getHex(x, y);
}

Point GameMap::getGridPosition(glm::vec2 screenPosition) {
	//TODO: Android Studio complains about this, but it builds fine. Find a way to silence it?
	auto position = screenPosition / camera.getZoom() + camera.getPosition() * gridSize;
	position.x /= gridSize;
	position.y /= gridSize;
	//debugPosition = getScreenPosition(position);

	int minX = (int)(position.x / xOffset);
	int minY = (int)position.y;
	int maxX = (int)(position.x / xOffset) + 1;
	int maxY = (int)position.y + 1;

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

glm::vec2 GameMap::getScreenPosition(glm::vec2 hexPosition) {
	return gridSize * hexPosition;
}

Actor* GameMap::createActor(Sprite* sprite, glm::vec2 position, float depth) {
	auto actor = new Actor(sprite, getScreenPosition(position), depth);
	auto actorPointer = std::unique_ptr<Actor>(actor);
	scene.addActor(actorPointer);
	return actor;
}

Actor* GameMap::createActor(
	Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> colors, float depth
) {
	auto actor = new RecoloredActor(sprite, getScreenPosition(position), depth, colors);
	auto actorPointer = std::unique_ptr<Actor>(actor);
	scene.addActor(actorPointer);
	return actor;
}

void GameMap::initializeHexes() {
	hexes.clear();
	hexes.reserve(width * height);

	auto assets = scenario->getCampaign()->getGame()->getAssets();
	HexType* grass = assets->getHexType("grass");
	for (uint16_t y = 0; y < width; y++) {
		for (uint16_t x = 0; x < height; x++) {
			auto hex = make_unique<MapHex>(x, y, grass, this);
			hexes.push_back(move(hex));
		}
	}

	for (auto& hex : hexes) {
		hex->initializeNeighbors();
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
