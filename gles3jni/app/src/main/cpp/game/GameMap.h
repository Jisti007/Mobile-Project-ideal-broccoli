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

class GameMap {
public:
	GameMap();
	GameMap(uint16_t width, uint16_t height, AssetManager* assets, Pipeline* pipeline);
	~GameMap();

	void initialize(uint16_t width, uint16_t height, AssetManager* assets, Pipeline* pipeline);
	void generate();
	void draw();

	inline MapHex* getHex(uint16_t x, uint16_t y) { return &hexes[y * width + x]; }
	inline Camera* getCamera() { return &camera; }
	inline uint16_t getWidth() { return width; }
	inline uint16_t getHeight() { return height; }

private:
	std::vector<MapRegion> regions;
	std::vector<MapRegion*> expanders;
	std::vector<MapHex> hexes;
	std::vector<Faction> factions;
	std::vector<std::unique_ptr<MapObject>> mapObjects;
	std::vector<Unit> units;
	uint16_t width;
	uint16_t height;
	Pipeline* pipeline;
	Camera camera;
	AssetManager* assets;

	void initializeHexes();
	void createRegions(int count);
	void expandRegions(int iterations, int maxPerRegion);
	void updateHexTypes();
	MapHex* findFreeHex(int maxTries);
	glm::vec2 getScreenPosition(int32_t x, int32_t y);
	int getDefaultMaxExpansionsPerRegion() {
		return (int) (hexes.size() / (1 + regions.capacity()));
	}
};

#endif //GLES3JNI_GAMEMAP_H
