#include "AssetManager.h"
#include "FileHelper.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace rapidxml;

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

void AssetManager::loadModule(const char *xmlPath) {
	// RapidXML does not copy strings,
	// so the source text must remain in scope for as long as we are reading it.
	auto text = FileHelper::ReadText(xmlPath);
	xml_document<> document;
	document.parse<0>(text.data());

	xml_node<> *root = document.first_node();
	xml_node<> *node = root->first_node();
	while (node) {
		if (strcmp(node->name(), "LoadAssets") == 0) {
			const char *assetXmlPath = node->first_attribute("path")->value();
			loadAssets(assetXmlPath);
		}
		node = node->next_sibling();
	}
}

void AssetManager::unloadAll() {
	textures.clear();
	hexTypes.clear();
	unitTypes.clear();
	buildingTypes.clear();
	resources.clear();
}

void AssetManager::loadAssets(const char *xmlPath) {
	// RapidXML does not copy strings,
	// so the source text must remain in scope for as long as we are reading it.
	auto text = FileHelper::ReadText(xmlPath);
	xml_document<> document;
	try {
		document.parse<0>(text.data());
	}
	catch (parse_error parseError) {
		return;
	}

	xml_node<> *root = document.first_node();
	xml_node<> *node = root->first_node();

	while (node) {
		if (strcmp(node->name(), "Texture") == 0) {
			loadTexture(node);
		}
		else if (strcmp(node->name(), "Hex") == 0) {
			loadHexType(node);
		}
		else if (strcmp(node->name(), "Unit") == 0) {
			loadUnitType(node);
		}
		else if (strcmp(node->name(), "Building") == 0) {
			loadBuildingType(node);
		}
		else if (strcmp(node->name(), "Resource") == 0) {
			loadResource(node);
		}

		node = node->next_sibling();
	}
}

void AssetManager::loadTexture(xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	const char* path = node->first_attribute("path")->value();
	unique_ptr<Texture> texture(new Texture(path));
	textures[id] = move(texture);
}

void AssetManager::loadHexType(xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	const char* textureId = node->first_attribute("texture")->value();
	Texture* texture = textures[textureId].get();
	hexTypes[id] = unique_ptr<HexType>(new HexType(texture));
}

void AssetManager::loadUnitType(rapidxml::xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	const char* textureId = node->first_attribute("texture")->value();
	Texture* texture = textures[textureId].get();
	unitTypes[id] = unique_ptr<UnitType>(new UnitType(texture));
}

void AssetManager::loadBuildingType(rapidxml::xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	const char* textureId = node->first_attribute("texture")->value();
	Texture* texture = textures[textureId].get();
	buildingTypes[id] = unique_ptr<BuildingType>(new BuildingType(texture));
}

void AssetManager::loadResource(rapidxml::xml_node<> *node) {
	const char* id = node->first_attribute("id")->value();
	const char* textureId = node->first_attribute("texture")->value();
	Texture* texture = textures[textureId].get();
	resources[id] = unique_ptr<Resource>(new Resource(texture));
}
