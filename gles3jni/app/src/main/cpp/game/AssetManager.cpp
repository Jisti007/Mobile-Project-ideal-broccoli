#include "AssetManager.h"
#include "FileHelper.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace rapidxml;
using placeholders::_1;

AssetManager::AssetManager() {
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

void AssetManager::loadModule(const char *xmlPath) {
	loadXml(xmlPath, bind(&AssetManager::handleModuleNode, this, _1));
}

void AssetManager::loadXml(const char *xmlPath, function<void(xml_node<>*)> nodeFunction) {
	// RapidXML does not copy strings,
	// so the source text must remain in scope for as long as we are referencing it.
	std::vector<char> text;
	xml_document<> document;
	try {
		text = FileHelper::ReadText(xmlPath);
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
	xml_node<> *node = root->first_node();
	while (node) {
		nodeFunction(node);
		node = node->next_sibling();
	}
}

void AssetManager::handleModuleNode(xml_node<> *node) {
	moduleFunctions[node->name()](node);
}

void AssetManager::loadAssets(xml_node<> *node) {
	const char *assetXmlPath = node->first_attribute("path")->value();
	loadXml(assetXmlPath, bind(&AssetManager::handleAssetNode, this, _1));
}

void AssetManager::handleAssetNode(xml_node<> *node) {
	assetFunctions[node->name()](node);
}

void AssetManager::loadTexture(xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	const char* path = node->first_attribute("path")->value();
	textures[id] = unique_ptr<Texture>(new Texture(path));
}

void AssetManager::loadHexType(xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	Texture* texture = getNodeTexture(node);
	hexTypes[id] = unique_ptr<HexType>(new HexType(texture));
}

void AssetManager::loadUnitType(xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	Texture* texture = getNodeTexture(node);
	unitTypes[id] = unique_ptr<UnitType>(new UnitType(texture));
}

void AssetManager::loadBuildingType(xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	Texture* texture = getNodeTexture(node);
	buildingTypes[id] = unique_ptr<BuildingType>(new BuildingType(texture));
}

void AssetManager::loadResource(xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	Texture* texture = getNodeTexture(node);
	resources[id] = unique_ptr<Resource>(new Resource(texture));
}

Texture *AssetManager::getNodeTexture(xml_node<> *node) {
	const char* textureId = node->first_attribute("texture")->value();
	return textures[textureId].get();
}
