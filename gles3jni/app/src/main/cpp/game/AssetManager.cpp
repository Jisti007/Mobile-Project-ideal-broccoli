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
		if (node->name() == "LoadAssets") {
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
		if (node->name() == "Texture") {
			const char* textureId = node->first_attribute("id")->value();
			const char* texturePath = node->first_attribute("path")->value();
			textures.emplace(textureId, texturePath);
		}
		else if (node->name() == "Hex") {

		}
		node = node->next_sibling();
	}
}
