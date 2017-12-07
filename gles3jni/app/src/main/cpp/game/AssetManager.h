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
	inline DamageType* getDamageType(const char* assetId) { return damageTypes[assetId].get(); }
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

	template <typename T>
	using StringMap = std::unordered_map<std::string, T>;

	template <typename T>
	using FunctionMap = StringMap<std::function<T>>;
	typedef FunctionMap<void(Node*)> VoidFunctionMap;
	VoidFunctionMap moduleFunctions;
	VoidFunctionMap assetFunctions;

	template <typename T>
	using PtrFunctionMap = FunctionMap<std::unique_ptr<T>(Node*)>;
	PtrFunctionMap<Effect> effectFunctions;
	PtrFunctionMap<SkillAnimation> animationFunctions;

	template <typename T>
	using AssetMap = StringMap<std::unique_ptr<T>>;
	AssetMap<Texture> textures;
	AssetMap<Mesh> meshes;
	AssetMap<Sprite> sprites;
	AssetMap<DamageType> damageTypes;
	AssetMap<HexType> hexTypes;
	AssetMap<Biome> biomes;
	AssetMap<UnitType> unitTypes;
	AssetMap<BuildingType> buildingTypes;
	AssetMap<Resource> resources;
	AssetMap<Font> fonts;
	WeightedList<Biome*> weightedBiomes;
	StringMap<SkillAnimation::Role> skillAnimationActors;
	StringMap<TargetType> targetTypes;

	void
	loadXml(const char* directory, const char* fileName, std::function<void(Node*)> nodeFunction);
	void handleModuleNode(Node* node);
	void loadAssets(Node* node);
	void handleAssetNode(Node* node);
	void loadTexture(Node* node);
	void loadSprite(Node* node);
	void loadSpriteUsing(Node* node, Texture* texture, const char* prefix);
	void loadSpriteUsing(
		Node* node, Texture* texture, const char* prefix, int y, int h, int yOffset
	);
	void loadSpriteSheet(Node* node);
	void loadDamageType(Node* node);
	void loadFont(Node* node);
	void loadHexType(Node* node);
	void loadBiome(Node* node);
	void loadUnitType(Node* node);
	void loadBuildingType(Node* node);
	void loadResource(Node* node);

	std::unique_ptr<Damage> loadDamage(Node* node);
	std::unique_ptr<Effect> loadHPModification(Node* node);
	std::unique_ptr<SkillAnimation> loadNudge(Node* node);
	std::unique_ptr<SkillAnimation> loadProjectile(Node* node);

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
		const char* getPriority() { return data->first_attribute("priority")->value(); }
		const char* getHP() { return data->first_attribute("hp")->value(); }

	private:
		const char* directory;
		rapidxml::xml_node<>* data;
	};
};

#endif //GLES3JNI_ASSETMANAGER_H
