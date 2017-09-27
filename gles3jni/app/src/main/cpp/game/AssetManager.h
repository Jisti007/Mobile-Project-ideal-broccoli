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
	inline Texture* getTexture(const char* assetId) { return textures[assetId].get(); }
	inline Mesh* getMesh(const char* assetId) { return meshes[assetId].get(); }
	inline Sprite* getSprite(const char* assetId) { return sprites[assetId].get(); }
	inline HexType* getHexType(const char* assetId) { return hexTypes[assetId].get(); }
	inline UnitType* getUnitType(const char* assetId) { return unitTypes[assetId].get(); }
	inline BuildingType* getBuildingType(const char* assetId) { return buildingTypes[assetId].get(); }
	inline Resource* getResource(const char* assetId) { return resources[assetId].get(); }

private:
	class Node;

	std::unordered_map<std::string, std::function<void(Node*)>> moduleFunctions;
	std::unordered_map<std::string, std::function<void(Node*)>> assetFunctions;
	std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
	std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;
	std::unordered_map<std::string, std::unique_ptr<Sprite>> sprites;
	std::unordered_map<std::string, std::unique_ptr<HexType>> hexTypes;
	std::unordered_map<std::string, std::unique_ptr<UnitType>> unitTypes;
	std::unordered_map<std::string, std::unique_ptr<BuildingType>> buildingTypes;
	std::unordered_map<std::string, std::unique_ptr<Resource>> resources;

	//void addAssetFunction(const char* key, void (AssetManager::* assetFunction)(Node*));
	void loadXml(const char *directory, const char* fileName, std::function<void(Node*)> nodeFunction);
	void handleModuleNode(Node *node);
	void loadAssets(Node *node);
	void handleAssetNode(Node *node);
	void loadTexture(Node *node);
	void loadSprite(Node *node);
	void loadHexType(Node *node);
	void loadUnitType(Node *node);
	void loadBuildingType(Node *node);
	void loadResource(Node *node);

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
		const char* getTexture() { return data->first_attribute("texture")->value(); }
		const char* getSprite() { return data->first_attribute("sprite")->value(); }
		const char* getX() { return data->first_attribute("x")->value(); }
		const char* getY() { return data->first_attribute("y")->value(); }
		const char* getW() { return data->first_attribute("w")->value(); }
		const char* getH() { return data->first_attribute("h")->value(); }

	private:
		const char* directory;
		rapidxml::xml_node<>* data;
	};
};

#endif //GLES3JNI_ASSETMANAGER_H
