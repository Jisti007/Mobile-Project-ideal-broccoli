#ifndef GLES3JNI_GAMEMAP_H
#define GLES3JNI_GAMEMAP_H


#include <vector>
#include <string>
#include "MapHex.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Actor.h"
#include "Scene.h"

class GameMap {
public:
	GameMap();
    GameMap(uint16_t width, uint16_t height, AssetManager& assets);
	~GameMap();

	void initialize(uint16_t width, uint16_t height, AssetManager &assets, Pipeline* pipeline);
	void draw();

	inline MapHex* getHex(uint16_t x, uint16_t y) { return &hexes[y * width + x]; }
	inline Scene* getScene() { return &scene; }

private:
	Scene scene;
    std::vector<MapHex> hexes;
	uint16_t width;
	uint16_t height;
};

#endif //GLES3JNI_GAMEMAP_H
