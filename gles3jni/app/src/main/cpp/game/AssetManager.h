#ifndef GLES3JNI_ASSETMANAGER_H
#define GLES3JNI_ASSETMANAGER_H

#include <vector>
#include <unordered_map>
#include "Texture.h"
#include "HexType.h"
#include "UnitType.h"
#include "BuildingType.h"
#include "Resource.h"

class AssetManager {
public:
	AssetManager();
	virtual ~AssetManager();

	void loadModule(const char* path);
	//virtual Texture* loadTexture(const char* filePath);

private:
	std::unordered_map<const char*, Texture> textures;
	std::unordered_map<const char*, HexType> hexTypes;
	std::unordered_map<const char*, UnitType> unitTypes;
	std::unordered_map<const char*, BuildingType> buildingTypes;
	std::unordered_map<const char*, Resource> resources;

	void loadAssets(const char* path);
};

#endif //GLES3JNI_ASSETMANAGER_H
