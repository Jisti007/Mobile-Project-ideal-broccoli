#include "AssetManager.h"
#include "FileHelper.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace rapidxml;
using placeholders::_1;

AssetManager::AssetManager() {
	// Bind functions to maps, primarily so we won't need if-else chains.
	// moduleFunctions and assetFunctions are separate to prevent possible recursion.
	moduleFunctions["LoadAssets"] = bind(&AssetManager::loadAssets, this, _1);
	assetFunctions["Texture"] = bind(&AssetManager::loadTexture, this, _1);
	assetFunctions["Sprite"] = bind(&AssetManager::loadSprite, this, _1);
	assetFunctions["SpriteSheet"] = bind(&AssetManager::loadSpriteSheet, this, _1);
	assetFunctions["Font"] = bind(&AssetManager::loadFont, this, _1);
	assetFunctions["Hex"] = bind(&AssetManager::loadHexType, this, _1);
	assetFunctions["Biome"] = bind(&AssetManager::loadBiome, this, _1);
	assetFunctions["Unit"] = bind(&AssetManager::loadUnitType, this, _1);
	assetFunctions["Building"] = bind(&AssetManager::loadBuildingType, this, _1);
	assetFunctions["Resource"] = bind(&AssetManager::loadResource, this, _1);
}

AssetManager::~AssetManager() {

}

void AssetManager::unloadAll() {
	textures.clear();
	sprites.clear();
	fonts.clear();
	hexTypes.clear();
	biomes.clear();
	weightedBiomes.clear();
	unitTypes.clear();
	buildingTypes.clear();
	resources.clear();
	loadedModules.clear();
}

void AssetManager::reloadAll() {
	for (auto& texture : textures) {
		if (texture.second != nullptr) {
			texture.second->initialize();
		}
	}
	for (auto& sprite : sprites) {
		if (sprite.second != nullptr) {
			sprite.second->reload();
		}
	}
}

void AssetManager::loadModule(const char *directory) {
	loadXml(directory, "Descriptor.xml", bind(&AssetManager::handleModuleNode, this, _1));
	loadedModules.insert(directory);
}

bool AssetManager::isModuleLoaded(const char * module) {
	return loadedModules.find(module) != loadedModules.end();
}

void AssetManager::loadXml(const char *directory, const char *fileName, function<void(Node*)> nodeFunction) {
	stringstream filePath;
	filePath << directory << "/" << fileName;

	std::vector<char> text;
	xml_document<> document;
	try {
		text = FileHelper::ReadText(filePath.str());
		document.parse<0>(text.data());
	}
	catch (runtime_error runtimeError) {
		//TODO: Could not load file. Also a more descriptive name for the error?
		return;
	}
	catch (parse_error parseError) {
		//TODO: Could not parse xml.
		return;
	}

	auto root = document.first_node();
	auto data = root->first_node();
	while (data) {
		Node node(directory, data);
		nodeFunction(&node);
		data = data->next_sibling();
	}
}

void AssetManager::handleModuleNode(Node *node) {
	moduleFunctions[node->getName()](node);
}

void AssetManager::loadAssets(Node *node) {
	loadXml(node->getDirectory(), node->getPath(), bind(&AssetManager::handleAssetNode, this, _1));
}

void AssetManager::handleAssetNode(Node *node) {
	assetFunctions[node->getName()](node);
}

void AssetManager::loadTexture(Node *node) {
	stringstream path;
	path << node->getDirectory() << "/" << node->getPath();
	auto id = node->getID();
	textures[id] = make_unique<Texture>(id, path.str().c_str());
}

void AssetManager::loadSprite(AssetManager::Node *node) {
	auto texture = textures[node->getTexture()].get();
	loadSprite2(node, texture);
}


void AssetManager::loadSprite2(AssetManager::Node* node, Texture* texture) {
	int xOffset = 0;
	int yOffset = 0;

	if(node->getData()->first_attribute("xOffset")) {
		yOffset = atoi(node->getData()->first_attribute("xOffset")->value());
	}
	if(node->getData()->first_attribute("yOffset")) {
		yOffset = atoi(node->getData()->first_attribute("yOffset")->value());
	}

	std::vector<glm::vec3> swappableColors;
	auto swappableColorNode = node->getData()->first_node("SwappableColor");
	while (swappableColorNode) {
		auto r = (float)atof(swappableColorNode->first_attribute("r")->value()) / 255.0f;
		auto g = (float)atof(swappableColorNode->first_attribute("g")->value()) / 255.0f;
		auto b = (float)atof(swappableColorNode->first_attribute("b")->value()) / 255.0f;
		swappableColors.emplace_back(r, g, b);

		swappableColorNode = swappableColorNode->next_sibling();
	}

	auto id = node->getID();
	sprites[id] = make_unique<Sprite>(
		id,
		texture,
		atoi(node->getX()),
		atoi(node->getY()),
		atoi(node->getW()),
		atoi(node->getH()),
		xOffset,
		yOffset,
		swappableColors
	);
}

void AssetManager::loadSpriteSheet(AssetManager::Node* node) {
	auto texture = textures[node->getTexture()].get();
	auto spriteNode = node->getData()->first_node("Sprite");
	while (spriteNode){
		Node node1(node->getDirectory(), spriteNode);
		loadSprite2(&node1, texture);
		spriteNode = spriteNode->next_sibling();
	}
}


void AssetManager::loadFont(AssetManager::Node* node) {
	std::unordered_map<char, Sprite*> mapping;
	auto mappingNode = node->getData()->first_node("SpriteMapping");
	while(mappingNode){
		auto mappingChar = mappingNode->first_attribute("char")->value()[0];
		auto sprite = sprites[mappingNode->first_attribute("sprite")->value()].get();

		mapping[mappingChar] = sprite;
		mappingNode = mappingNode->next_sibling();
	}
	fonts[node->getID()] = make_unique<Font>(mapping);
}


void AssetManager::loadHexType(Node *node) {
	auto sprite = sprites[node->getSprite()].get();
	auto movementCost = (float)atof(node->getMovementCost());
	hexTypes[node->getID()] = make_unique<HexType>(sprite, movementCost);
}

void AssetManager::loadBiome(AssetManager::Node* node) {
	WeightedList<HexType*> biomeHexes;
	auto hexNode = node->getData()->first_node("Hex");
	while (hexNode) {
		auto hexId = hexNode->first_attribute("id")->value();
		auto hexType = getHexType(hexId);
		double hexWeight = atof(hexNode->first_attribute("weight")->value());
		biomeHexes.add(hexType, hexWeight);

		hexNode = hexNode->next_sibling();
	}

	auto biome = new Biome(biomeHexes);
	biomes[node->getID()] = unique_ptr<Biome>(biome);
	weightedBiomes.add(biome, atof(node->getWeight()));
}

void AssetManager::loadUnitType(Node *node) {
	auto sprite = sprites[node->getSprite()].get();
	unitTypes[node->getID()] = make_unique<UnitType>(sprite);
}

void AssetManager::loadBuildingType(Node *node) {
	auto sprite = sprites[node->getSprite()].get();
	buildingTypes[node->getID()] = make_unique<BuildingType>(sprite);
}

void AssetManager::loadResource(Node *node) {
	auto sprite = sprites[node->getSprite()].get();
	resources[node->getID()] = make_unique<Resource>(sprite);
}

