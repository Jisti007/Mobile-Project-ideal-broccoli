#ifndef GLES3JNI_ASSETMANAGER_H
#define GLES3JNI_ASSETMANAGER_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "../rapidxml.hpp"
#include "Texture.h"
#include "HexType.h"
#include "UnitType.h"
#include "BuildingType.h"
#include "Resource.h"

class AssetManager {
public:
	AssetManager();
	virtual ~AssetManager();

	void unloadAll();
	void loadModule(const char* xmlPath);
	Texture* getTexture(const char* textureAssetId) { return textures[textureAssetId].get(); }
	HexType* getHexType(const char* hexTypeAssetId) { return hexTypes[hexTypeAssetId].get(); }
	HexType* getUnitType(const char* unitAssetId) { return hexTypes[unitAssetId].get(); }
	HexType* getBuildingType(const char* buildingAssetId) { return hexTypes[buildingAssetId].get(); }
	HexType* getResource(const char* resourceAssetId) { return hexTypes[resourceAssetId].get(); }

private:
	std::unordered_map<std::string, std::function<void(rapidxml::xml_node<>*)>> moduleFunctions;
	std::unordered_map<std::string, std::function<void(rapidxml::xml_node<>*)>> assetFunctions;
	std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
	std::unordered_map<std::string, std::unique_ptr<HexType>> hexTypes;
	std::unordered_map<std::string, std::unique_ptr<UnitType>> unitTypes;
	std::unordered_map<std::string, std::unique_ptr<BuildingType>> buildingTypes;
	std::unordered_map<std::string, std::unique_ptr<Resource>> resources;

	void loadXml(const char* xmlPath, std::function<void(rapidxml::xml_node<>*)> nodeFunction);
	void handleModuleNode(rapidxml::xml_node<> *node);
	void loadAssets(rapidxml::xml_node<> *node);
	void handleAssetNode(rapidxml::xml_node<> *node);
	void loadTexture(rapidxml::xml_node<> *node);
	void loadHexType(rapidxml::xml_node<> *node);
	void loadUnitType(rapidxml::xml_node<> *node);
	void loadBuildingType(rapidxml::xml_node<> *node);
	void loadResource(rapidxml::xml_node<> *node);
	Texture* getNodeTexture(rapidxml::xml_node<> *node);
};

#endif //GLES3JNI_ASSETMANAGER_H
