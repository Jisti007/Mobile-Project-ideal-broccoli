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
	assetFunctions["Hex"] = bind(&AssetManager::loadHexType, this, _1);
	assetFunctions["Unit"] = bind(&AssetManager::loadUnitType, this, _1);
	assetFunctions["Building"] = bind(&AssetManager::loadBuildingType, this, _1);
	assetFunctions["Resource"] = bind(&AssetManager::loadResource, this, _1);

	//addAssetFunction("LoadAssets", loadAssets);
}

AssetManager::~AssetManager() {

}

void AssetManager::unloadAll() {
	textures.clear();
	hexTypes.clear();
	unitTypes.clear();
	buildingTypes.clear();
	resources.clear();
}

void AssetManager::loadModule(const char *directory) {
	loadXml(directory, "Descriptor.xml", bind(&AssetManager::handleModuleNode, this, _1));
}
/*
void AssetManager::addAssetFunction(const char *key, void (*assetFunction)(Node *)) {

}
*/
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
	textures[node->getID()] = unique_ptr<Texture>(new Texture(path.str().c_str()));
}

void AssetManager::loadSprite(AssetManager::Node *node) {
	auto texture = textures[node->getTexture()].get();
	sprites[node->getID()] = unique_ptr<Sprite>(new Sprite(
		texture,
		atoi(node->getX()),
		atoi(node->getY()),
		atoi(node->getW()),
		atoi(node->getH())
	));
}

void AssetManager::loadHexType(Node *node) {
	auto sprite = sprites[node->getSprite()].get();
	hexTypes[node->getID()] = unique_ptr<HexType>(new HexType(sprite));
}

void AssetManager::loadUnitType(Node *node) {
	auto texture = textures[node->getTexture()].get();
	unitTypes[node->getID()] = unique_ptr<UnitType>(new UnitType(texture));
}

void AssetManager::loadBuildingType(Node *node) {
	auto texture = textures[node->getTexture()].get();
	buildingTypes[node->getID()] = unique_ptr<BuildingType>(new BuildingType(texture));
}

void AssetManager::loadResource(Node *node) {
	auto texture = textures[node->getTexture()].get();
	resources[node->getID()] = unique_ptr<Resource>(new Resource(texture));
}
