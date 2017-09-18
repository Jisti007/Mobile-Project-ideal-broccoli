#include "AssetManager.h"

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {
	for (auto texture : textures) {
		delete texture;
	}
}

Texture *AssetManager::loadTexture(const char *filePath) {
	auto texture = new Texture(filePath);
	textures.push_back(texture);
	return texture;
}
