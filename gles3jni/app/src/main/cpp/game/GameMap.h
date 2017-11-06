#ifndef GLES3JNI_GAMEMAP_H
#define GLES3JNI_GAMEMAP_H

class MapHex;

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

class GameMap {
public:
	GameMap();
	GameMap(uint16_t width, uint16_t height, AssetManager* assets, Pipeline* pipeline);
	~GameMap();

	void initialize(uint16_t width, uint16_t height, AssetManager* assets, Pipeline* pipeline);
	void generate();
	void draw();
	Unit* createUnit(Point position, UnitType* type, Faction* faction);
	/// Returns nullptr if out of bounds.
	MapHex* tryGetHex(int x, int y);
	Point getGridPosition(glm::vec2 screenPosition);

	inline MapHex* getHex(int x, int y) { return hexes[y * width + x].get(); }
	inline MapHex* tryGetHex(Point position) { return tryGetHex(position.x, position.y); }
	inline Camera* getCamera() { return &camera; }
	inline uint16_t getWidth() { return width; }
	inline uint16_t getHeight() { return height; }
	inline Faction* getFaction(int index) { return &factions[index]; }

private:
	std::vector<MapRegion> regions;
	std::vector<MapRegion*> expanders;
	std::vector<Faction> factions;
	std::vector<std::unique_ptr<MapHex>> hexes;
	std::vector<std::unique_ptr<MapObject>> mapObjects;
	std::vector<std::unique_ptr<Unit>> units;
	uint16_t width;
	uint16_t height;
	Pipeline* pipeline;
	Camera camera;
	AssetManager* assets;

	void initializeHexes();
	void initializeRegions(int count);
	void expandRegions(int iterations, int maxPerRegion);
	//void updateHexTypes();
	MapHex* findFreeHex(int maxTries);
	glm::vec2 getHexPosition(int x, int y);
	glm::vec2 getScreenPosition(int32_t x, int32_t y);
	int getDefaultMaxExpansionsPerRegion() {
		return (int) (hexes.size() / (1 + regions.size()));
	}
};

#endif //GLES3JNI_GAMEMAP_H
