#ifndef GLES3JNI_GAMEMAP_H
#define GLES3JNI_GAMEMAP_H

class MapHex;
class Scenario;

#include <vector>
#include <string>
#include "MapHex.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Pipeline.h"
#include "Camera.h"
#include "Building.h"
#include "MapObject.h"
#include "Faction.h"
#include "Point.h"
#include "Scenario.h"
#include "scenes/Scene.h"

class GameMap {
public:
	GameMap();
	GameMap(uint16_t width, uint16_t height, Scenario* scenario);
	~GameMap();

	void initialize(uint16_t width, uint16_t height, Scenario* scenario);
	void generate();
	void draw(float deltaTime);
	void onBeginTurn();
	Unit* createUnit(Point position, UnitType* type, Faction* faction);
	void removeUnit(Unit* unit);
	Building* createBuilding(Point position, BuildingType* type, Faction* faction);
	/// Returns nullptr if out of bounds. Otherwise returns the hex at the given grid coordinates.
	MapHex* tryGetHex(int x, int y);
	/// Transforms the given screen coordinates to grid coordinates.
	Point getGridPosition(glm::vec2 screenPosition);
	/// Transforms the given grid position to a normalized (pre-screen transform) hex position.
	glm::vec2 getHexPosition(int x, int y);
	/// Transforms the given hex position to screen coordinates.
	glm::vec2 getScreenPosition(glm::vec2 hexPosition);
	glm::vec2 getScreenPosition(Point gridPosition);

	inline Scenario* getScenario() { return scenario; }
	inline Scene* getScene() { return &scene; }
	inline MapHex* getHex(int x, int y) { return hexes[y * width + x].get(); }
	inline MapHex* tryGetHex(Point position) { return tryGetHex(position.x, position.y); }
	inline Camera* getCamera() { return &camera; }
	inline uint16_t getWidth() { return width; }
	inline uint16_t getHeight() { return height; }
	inline std::vector<std::unique_ptr<Unit>>& getUnits() { return units; }

	static const float gridSize;
	static const float xOffset;
	static const float yOffset;

private:
	Scene scene;
	Scenario* scenario;
	std::vector<MapRegion> regions;
	std::vector<MapRegion*> expanders;
	std::vector<std::unique_ptr<MapHex>> hexes;
	std::vector<std::unique_ptr<Building>> buildings;
	std::vector<std::unique_ptr<Unit>> units;
	uint16_t width;
	uint16_t height;
	Camera camera;
	//glm::vec2 debugPosition;

	Actor* createActor(Sprite* sprite, glm::vec2 position, float depth);
	Actor* createActor(Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> colors, float depth);
	void initializeHexes();
	void initializeRegions(int count);
	void expandRegions(int iterations, int maxPerRegion);
	MapHex* findFreeHex(int maxTries);
	glm::vec2 getScreenPosition(int32_t x, int32_t y);

	inline int getDefaultMaxExpansionsPerRegion() {
		return (int) (hexes.size() / (1 + regions.size()));
	}
};

#endif //GLES3JNI_GAMEMAP_H
