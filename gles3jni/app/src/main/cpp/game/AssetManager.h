#ifndef GLES3JNI_ASSETMANAGER_H
#define GLES3JNI_ASSETMANAGER_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "../rapidxml.hpp"
#include "Texture.h"
#include "HexType.h"
#include "UnitType.h"
#include "BuildingType.h"
#include "Resource.h"
#include "Biome.h"
#include "Font.h"

class AssetManager {
public:
	AssetManager();
	virtual ~AssetManager();

	void unloadAll();
	void reloadAll();
	void loadModule(const char* directory);

	bool isModuleLoaded(const char* module);

	inline Texture* getTexture(const char* assetId) { return textures[assetId].get(); }
	inline Mesh* getMesh(const char* assetId) { return meshes[assetId].get(); }
	inline Sprite* getSprite(const char* assetId) { return sprites[assetId].get(); }
	inline HexType* getHexType(const char* assetId) { return hexTypes[assetId].get(); }
	inline size_t getHexTypeCount() { return hexTypes.size(); }
	inline UnitType* getUnitType(const char* assetId) { return unitTypes[assetId].get(); }
	inline BuildingType* getBuildingType(const char* assetId) { return buildingTypes[assetId].get(); }
	inline Resource* getResource(const char* assetId) { return resources[assetId].get(); }
	inline Biome* getRandomBiome() { return weightedBiomes.getRandom(); }
	inline Font* getFont(const char* assetId) { return fonts[assetId].get(); }

private:
	class Node;

	std::unordered_set<std::string> loadedModules;

	typedef std::unordered_map<std::string, std::function<void(Node*)>> NodeFunction;
	NodeFunction moduleFunctions;
	NodeFunction assetFunctions;

	template<typename T>
	using AssetMap = std::unordered_map<std::string, std::unique_ptr<T>>;
	AssetMap<Texture> textures;
	AssetMap<Mesh> meshes;
	AssetMap<Sprite> sprites;
	AssetMap<HexType> hexTypes;
	AssetMap<Biome> biomes;
	AssetMap<UnitType> unitTypes;
	AssetMap<BuildingType> buildingTypes;
	AssetMap<Resource> resources;
	AssetMap<Font> fonts;
	WeightedList<Biome*> weightedBiomes;

	void
	loadXml(const char* directory, const char* fileName, std::function<void(Node*)> nodeFunction);
	void handleModuleNode(Node* node);
	void loadAssets(Node* node);
	void handleAssetNode(Node* node);
	void loadTexture(Node* node);
	void loadSprite(Node* node);
	void loadSpriteUsing(Node* node, Texture* texture, const char* prefix);
	void loadSpriteUsing(Node* node, Texture* texture, const char* prefix, int y, int h);
	void loadSpriteSheet(Node* node);
	void loadFont(Node* node);
	void loadHexType(Node* node);
	void loadBiome(Node* node);
	void loadUnitType(Node* node);
	void loadBuildingType(Node* node);
	void loadResource(Node* node);


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
		const char* getWeight() { return data->first_attribute("weight")->value(); }
		const char* getMovementCost() { return data->first_attribute("movementCost")->value(); }

	private:
		const char* directory;
		rapidxml::xml_node<>* data;
	};
};

#endif //GLES3JNI_ASSETMANAGER_H
