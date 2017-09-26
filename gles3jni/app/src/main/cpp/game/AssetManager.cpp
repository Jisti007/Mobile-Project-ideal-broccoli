#include "AssetManager.h"
#include "FileHelper.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace rapidxml;
using placeholders::_1;

AssetManager::AssetManager() {
	// Map functions, primarily so we won't need if-else chains.
	// moduleFunctions and assetFunctions are separate to prevent possible recursion.
	moduleFunctions["LoadAssets"] = bind(&AssetManager::loadAssets, this, _1);
	assetFunctions["Texture"] = bind(&AssetManager::loadTexture, this, _1);
	assetFunctions["Hex"] = bind(&AssetManager::loadHexType, this, _1);
	assetFunctions["Unit"] = bind(&AssetManager::loadUnitType, this, _1);
	assetFunctions["Building"] = bind(&AssetManager::loadBuildingType, this, _1);
	assetFunctions["Resource"] = bind(&AssetManager::loadResource, this, _1);
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

	xml_node<> *root = document.first_node();
	xml_node<> *data = root->first_node();
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

void AssetManager::loadHexType(Node *node) {
	Texture* texture = getNodeTexture(node);
	hexTypes[node->getID()] = unique_ptr<HexType>(new HexType(texture));
}

void AssetManager::loadUnitType(Node *node) {
	Texture* texture = getNodeTexture(node);
	unitTypes[node->getID()] = unique_ptr<UnitType>(new UnitType(texture));
}

void AssetManager::loadBuildingType(Node *node) {
	Texture* texture = getNodeTexture(node);
	buildingTypes[node->getID()] = unique_ptr<BuildingType>(new BuildingType(texture));
}

void AssetManager::loadResource(Node *node) {
	Texture* texture = getNodeTexture(node);
	resources[node->getID()] = unique_ptr<Resource>(new Resource(texture));
}

Texture *AssetManager::getNodeTexture(Node *node) {
	const char* textureId = node->getData()->first_attribute("texture")->value();
	return textures[textureId].get();
}
