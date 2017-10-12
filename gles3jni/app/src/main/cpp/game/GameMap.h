#ifndef GLES3JNI_GAMEMAP_H
#define GLES3JNI_GAMEMAP_H


#include <vector>
#include <string>
#include "MapHex.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Pipeline.h"
#include "Camera.h"
#include "Building.h"

class GameMap {
public:
	GameMap();
	GameMap(uint16_t width, uint16_t height, AssetManager &assets);
	~GameMap();

	void initialize(uint16_t width, uint16_t height, AssetManager &assets, Pipeline* pipeline);
	void draw();

	inline MapHex* getHex(uint16_t x, uint16_t y) { return &hexes[y * width + x]; }
	inline Unit* getUnit(uint16_t x, uint16_t y) { return &units[y * width + x]; }
	inline Camera* getCamera() { return &camera; }

private:
	std::vector<MapHex> hexes;
	std::vector<Unit> units;
	std::vector<Building> buildings;
	uint16_t width;
	uint16_t height;
	Pipeline* pipeline;
	Camera camera;

	glm::vec2 getScreenPosition(int32_t x, int32_t y);
};

#endif //GLES3JNI_GAMEMAP_H
