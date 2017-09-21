#include "AssetManager.h"
#include "../rapidxml.hpp"
#include "FileHelper.h"

using namespace rapidxml;

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

void AssetManager::loadModule(const char *path) {
	// RapidXML does not copy strings,
	// so the source text must remain in scope for as long as we are reading it.
	auto text = FileHelper::ReadText(path);
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

void AssetManager::loadAssets(const char *path) {
	// RapidXML does not copy strings,
	// so the source text must remain in scope for as long as we are reading it.
	auto text = FileHelper::ReadText(path);
	xml_document<> document;
	document.parse<0>(text.data());

	xml_node<> *root = document.first_node();
	xml_node<> *node = root->first_node();
	while (node) {
		if (strcmp(node->name(), "Texture") == 0) {
			const char* textureId = node->first_attribute("id")->value();
			const char* texturePath = node->first_attribute("path")->value();
			std::unique_ptr<Texture> texture(new Texture(texturePath));
			textures[textureId] = std::move(texture);
		}
		else if (strcmp(node->name(), "Hex") == 0) {
			const char* hexTypeId = node->first_attribute("id")->value();
			std::unique_ptr<HexType> hexType(new HexType());
			hexTypes[hexTypeId] = std::move(hexType);
		}
		node = node->next_sibling();
	}
}
