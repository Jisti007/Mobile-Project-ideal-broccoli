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
	void loadModule(const char* directory);
	Texture* getTexture(const char* textureAssetId) { return textures[textureAssetId].get(); }
	HexType* getHexType(const char* hexTypeAssetId) { return hexTypes[hexTypeAssetId].get(); }
	HexType* getUnitType(const char* unitAssetId) { return hexTypes[unitAssetId].get(); }
	HexType* getBuildingType(const char* buildingAssetId) { return hexTypes[buildingAssetId].get(); }
	HexType* getResource(const char* resourceAssetId) { return hexTypes[resourceAssetId].get(); }

private:
	class Node;

	std::unordered_map<std::string, std::function<void(Node*)>> moduleFunctions;
	std::unordered_map<std::string, std::function<void(Node*)>> assetFunctions;
	std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
	std::unordered_map<std::string, std::unique_ptr<HexType>> hexTypes;
	std::unordered_map<std::string, std::unique_ptr<UnitType>> unitTypes;
	std::unordered_map<std::string, std::unique_ptr<BuildingType>> buildingTypes;
	std::unordered_map<std::string, std::unique_ptr<Resource>> resources;

	void loadXml(const char *directory, const char* fileName, std::function<void(Node*)> nodeFunction);
	void handleModuleNode(Node *node);
	void loadAssets(Node *node);
	void handleAssetNode(Node *node);
	void loadTexture(Node *node);
	void loadHexType(Node *node);
	void loadUnitType(Node *node);
	void loadBuildingType(Node *node);
	void loadResource(Node *node);
	Texture* getNodeTexture(Node *node);

	class Node {
	public:
		Node(const char* directory, rapidxml::xml_node<>* data) {
			this->directory = directory;
			this->data = data;
		}

		const char* getDirectory() { return directory; }
		rapidxml::xml_node<>* getData() { return data; }

		const char* getName() { return data->name(); }
		const char* getID() { return data->first_attribute("id")->value(); }
		const char* getPath() { return data->first_attribute("path")->value(); }

	private:
		const char* directory;
		rapidxml::xml_node<>* data;
	};
};

#endif //GLES3JNI_ASSETMANAGER_H
