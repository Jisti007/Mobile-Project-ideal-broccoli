#ifndef GLES3JNI_ASSETMANAGER_H
#define GLES3JNI_ASSETMANAGER_H

#include <vector>
#include <memory>
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
	Texture* getTexture(const char* textureAssetId) { return textures[textureAssetId].get(); }
	HexType* getHexType(const char* hexTypeAssetId) { return hexTypes[hexTypeAssetId].get(); }
	HexType* getUnitType(const char* unitAssetId) { return hexTypes[unitAssetId].get(); }
	HexType* getBuildingType(const char* buildingAssetId) { return hexTypes[buildingAssetId].get(); }
	HexType* getResource(const char* resourceAssetId) { return hexTypes[resourceAssetId].get(); }

private:
	std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
	std::unordered_map<std::string, std::unique_ptr<HexType>> hexTypes;
	std::unordered_map<std::string, std::unique_ptr<UnitType>> unitTypes;
	std::unordered_map<std::string, std::unique_ptr<BuildingType>> buildingTypes;
	std::unordered_map<std::string, std::unique_ptr<Resource>> resources;

	void loadAssets(const char* path);
};

#endif //GLES3JNI_ASSETMANAGER_H
