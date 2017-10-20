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
#include "MapObject.h"

class GameMap {
public:
	GameMap();
	GameMap(uint16_t width, uint16_t height, AssetManager *assets);
	~GameMap();

	void initialize(uint16_t width, uint16_t height, AssetManager *assets, Pipeline* pipeline);
	void generate();
	void draw();

	inline MapHex* getHex(uint16_t x, uint16_t y) { return &hexes[y * width + x]; }
	inline Camera* getCamera() { return &camera; }

private:
	std::vector<MapHex> hexes;
	std::vector<std::unique_ptr<MapObject>> mapObjects;
	uint16_t width;
	uint16_t height;
	Pipeline* pipeline;
	Camera camera;
	AssetManager* assets;

	glm::vec2 getScreenPosition(int32_t x, int32_t y);
};

#endif //GLES3JNI_GAMEMAP_H
