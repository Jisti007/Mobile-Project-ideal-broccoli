#include "Ruleset.h"
#include "FileHelper.h"
#include "../rapidxml.hpp"

using namespace rapidxml;

Ruleset::Ruleset(const char *xmlPath) {
	// RapidXML does not copy strings,
	// so the source text must remain in scope for as long as we are reading it.
	auto text = FileHelper::ReadText(xmlPath);
	xml_document<> document;
	document.parse<0>(text.data());

	xml_node<> *root = document.first_node();
	xml_node<> *node = root->first_node();
	do {
		if (node->name() == "LoadAssets") {
			const char *path = node->first_attribute("path")->value();
			loadAssets(xmlPath);
		}
	}
	while (node->next_sibling());
}

Ruleset::~Ruleset() {

}

void Ruleset::loadAssets(const char *xmlPath) {
	// RapidXML does not copy strings,
	// so the source text must remain in scope for as long as we are reading it.
	auto text = FileHelper::ReadText(xmlPath);
	xml_document<> document;
	document.parse<0>(text.data());

	xml_node<> *root = document.first_node();
	xml_node<> *node = root->first_node();
	do {
		if (node->name() == "Texture") {
			const char* textureId = node->first_attribute("id")->value();
			const char* texturePath = node->first_attribute("path")->value();
			textures.emplace(textureId, texturePath);
		}
		else if (node->name() == "Hex") {

		}
	}
	while (node->next_sibling());
}
