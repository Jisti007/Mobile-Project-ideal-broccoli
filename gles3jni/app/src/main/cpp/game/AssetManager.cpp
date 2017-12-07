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
	moduleFunctions["LoadAssets"] = std::bind(&AssetManager::loadAssets, this, _1);

	assetFunctions["Texture"] = std::bind(&AssetManager::loadTexture, this, _1);
	assetFunctions["Sprite"] = std::bind(&AssetManager::loadSprite, this, _1);
	assetFunctions["SpriteSheet"] = std::bind(&AssetManager::loadSpriteSheet, this, _1);
	assetFunctions["Font"] = std::bind(&AssetManager::loadFont, this, _1);
	assetFunctions["Hex"] = std::bind(&AssetManager::loadHexType, this, _1);
	assetFunctions["Biome"] = std::bind(&AssetManager::loadBiome, this, _1);
	assetFunctions["Unit"] = std::bind(&AssetManager::loadUnitType, this, _1);
	assetFunctions["Building"] = std::bind(&AssetManager::loadBuildingType, this, _1);
	assetFunctions["Resource"] = std::bind(&AssetManager::loadResource, this, _1);

	effectFunctions["HPModification"] = std::bind(&AssetManager::loadHPModification, this, _1);

	animationFunctions["Nudge"] = std::bind(&AssetManager::loadNudge, this, _1);
	animationFunctions["Projectile"] = std::bind(&AssetManager::loadProjectile, this, _1);

	skillAnimationActors["user"] = SkillAnimation::Role::user;
	skillAnimationActors["target"] = SkillAnimation::Role::target;

	targetTypes["enemy"] = TargetType::enemy;
	targetTypes["friendly"] = TargetType::friendly;
	targetTypes["unit"] = TargetType::unit;
	targetTypes["hex"] = TargetType::hex;
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

void AssetManager::loadModule(const char* directory) {
	loadXml(directory, "_Module.xml", bind(&AssetManager::handleModuleNode, this, _1));
	loadedModules.insert(std::string(directory));
}

bool AssetManager::isModuleLoaded(const char* module) {
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
	loadSpriteUsing(node, texture, "");
}


void AssetManager::loadSpriteUsing(AssetManager::Node* node, Texture* texture, const char* prefix) {
	int y = atoi(node->getY());
	int h = atoi(node->getH());
	int yOffset = 0;
	auto yOffsetAttribute = node->getData()->first_attribute("yOffset");
	if (yOffsetAttribute) {
		yOffset = atoi(yOffsetAttribute->value());
	}
	loadSpriteUsing(node, texture, prefix, y, h, yOffset);
}

void AssetManager::loadSpriteUsing(
	AssetManager::Node* node, Texture* texture, const char* prefix, int y, int h, int yOffset
) {
	int xOffset = 0;
	//int yOffset = 0;

	if(node->getData()->first_attribute("xOffset")) {
		yOffset = atoi(node->getData()->first_attribute("xOffset")->value());
	}
	/*
	if(node->getData()->first_attribute("yOffset")) {
		yOffset = atoi(node->getData()->first_attribute("yOffset")->value());
	}
	*/

	std::vector<glm::vec3> swappableColors;
	auto swappableColorNode = node->getData()->first_node("SwappableColor");
	while (swappableColorNode) {
		auto r = (float)atof(swappableColorNode->first_attribute("r")->value()) / 255.0f;
		auto g = (float)atof(swappableColorNode->first_attribute("g")->value()) / 255.0f;
		auto b = (float)atof(swappableColorNode->first_attribute("b")->value()) / 255.0f;
		swappableColors.emplace_back(r, g, b);

		swappableColorNode = swappableColorNode->next_sibling();
	}

	std::string id = prefix;
	id += node->getID();
	sprites[id] = make_unique<Sprite>(
		id.c_str(),
		texture,
		atoi(node->getX()),
		y,
		atoi(node->getW()),
		h,
		xOffset,
		yOffset,
		swappableColors
	);
}

void AssetManager::loadSpriteSheet(AssetManager::Node* node) {
	auto texture = textures[node->getTexture()].get();
	std::string prefix = "";
	if (node->getData()->first_attribute("prefix")) {
		prefix = node->getData()->first_attribute("prefix")->value();
	}

	auto rowNode = node->getData()->first_node("Row");
	while (rowNode) {
		int y = atoi(rowNode->first_attribute("y")->value());
		int h = atoi(rowNode->first_attribute("h")->value());
		int yOffset = 0;
		auto yOffsetAttribute = rowNode->first_attribute("yOffset");
		if (yOffsetAttribute) {
			yOffset = atoi(yOffsetAttribute->value());
		}
		auto rowSpriteNode = rowNode->first_node("Sprite");
		while (rowSpriteNode) {
			Node node1(node->getDirectory(), rowSpriteNode);
			loadSpriteUsing(&node1, texture, prefix.c_str(), y, h, yOffset);
			rowSpriteNode = rowSpriteNode->next_sibling();
		}
		rowNode = rowNode->next_sibling("Row");
	}

	auto spriteNode = node->getData()->first_node("Sprite");
	while (spriteNode) {
		Node node1(node->getDirectory(), spriteNode);
		loadSpriteUsing(&node1, texture, prefix.c_str());
		spriteNode = spriteNode->next_sibling("Sprite");
	}
}

void AssetManager::loadFont(AssetManager::Node* node) {
	std::unordered_map<char, Sprite*> mappings;
	auto mappingNode = node->getData()->first_node("SpriteMapping");
	while(mappingNode){
		auto mappingChar = mappingNode->first_attribute("char")->value()[0];
		auto sprite = sprites[mappingNode->first_attribute("sprite")->value()].get();

		mappings[mappingChar] = sprite;
		mappingNode = mappingNode->next_sibling();
	}
	fonts[node->getID()] = std::make_unique<Font>(mappings);
}

void AssetManager::loadHexType(Node *node) {
	auto data = node->getData();
	auto sprite = sprites[node->getSprite()].get();
	auto movementCost = (float)atof(node->getMovementCost());
	WeightedList<Decoration> decorations;
	int minDecorations = 0;
	int maxDecorations = 0;
	auto decorationDistance = 0.0f;
	auto decorationsNode = data->first_node("Decorations");
	if (decorationsNode) {
		minDecorations = atoi(decorationsNode->first_attribute("min")->value());
		maxDecorations = atoi(decorationsNode->first_attribute("max")->value());
		decorationDistance = static_cast<float>(
			atof(decorationsNode->first_attribute("distance")->value())
		);
		auto decorationNode = decorationsNode->first_node("Decoration");
		while (decorationNode) {
			auto decorationSprite = getSprite(decorationNode->first_attribute("sprite")->value());
			auto weight = atof(decorationNode->first_attribute("weight")->value());
			Decoration decoration(decorationSprite);
			decorations.add(decoration, weight);

			decorationNode = decorationNode->next_sibling();
		}
	}

	hexTypes[node->getID()] = std::make_unique<HexType>(
		sprite, movementCost, decorations, minDecorations, maxDecorations, decorationDistance
	);
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
	biomes[node->getID()] = std::unique_ptr<Biome>(biome);
	weightedBiomes.add(biome, atof(node->getWeight()));
}

void AssetManager::loadUnitType(Node *node) {
	auto sprite = sprites[node->getSprite()].get();
	auto data = node->getData();
	auto hp = atoi(node->getHP());
	auto defense = atoi(data->first_attribute("defense")->value());
	auto movement = atoi(data->first_attribute("movement")->value());
	UnitType::SkillList skills;

	auto skillNode = node->getData()->first_node("Skill");
	while (skillNode) {
		auto skillSprite = getSprite(skillNode->first_attribute("sprite")->value());
		auto targetType = targetTypes[skillNode->first_attribute("target")->value()];
		auto skillRange = atoi(skillNode->first_attribute("range")->value());
		auto skillCost = atof(skillNode->first_attribute("cost")->value());

		Skill::EffectList effects;
		auto effectNode = skillNode->first_node("Effects")->first_node();
		while (effectNode) {
			auto function = effectFunctions[effectNode->name()];
			if (function) {
				Node effectNode2(node->getDirectory(), effectNode);
				auto effect = function(&effectNode2);
				// Android Studio gives a false error. Compiles fine.
				effects.push_back(std::move(effect));
			}

			effectNode = effectNode->next_sibling();
		}

		Skill::AnimationList animations;
		auto animationNode = skillNode->first_node("Animations")->first_node();
		while (animationNode) {
			auto function = animationFunctions[animationNode->name()];
			if (function) {
				Node animationNode2(node->getDirectory(), animationNode);
				auto animation = function(&animationNode2);
				// Android Studio gives a false error. Compiles fine.
				animations.push_back(std::move(animation));
			}

			animationNode = animationNode->next_sibling();
		}

		skills.push_back(std::make_unique<Skill>(
			skillSprite, targetType, skillRange, skillCost, effects, animations
		));

		skillNode = skillNode->next_sibling();
	}

	unitTypes[node->getID()] = std::make_unique<UnitType>(
		sprite, hp, defense, movement, skills
	);
}

void AssetManager::loadBuildingType(Node *node) {
	auto sprite = sprites[node->getSprite()].get();

	std::vector<std::pair<Resource*, int>> resourceProductions;
	auto productionNode = node->getData()->first_node("ResourceProduction");
	while(productionNode){
		auto resource = productionNode->first_attribute("resource")->value();
		auto amount = atoi(productionNode->first_attribute("amount")->value());

		resourceProductions.push_back(
			std::pair<Resource*, int>(getResource(resource), amount)
		);
		productionNode = productionNode->next_sibling("ResourceProduction");
	}

	buildingTypes[node->getID()] = std::make_unique<BuildingType>(sprite, resourceProductions);
}

void AssetManager::loadResource(Node *node) {
	auto sprite = sprites[node->getSprite()].get();
	auto priority = atoi(node->getPriority());
	resources[node->getID()] = std::make_unique<Resource>(sprite, priority);
}

std::unique_ptr<Effect> AssetManager::loadHPModification(AssetManager::Node* node) {
	auto amount = atoi(node->getData()->first_attribute("amount")->value());
	return std::unique_ptr<Effect>(new HPModification(amount));
}

std::unique_ptr<SkillAnimation> AssetManager::loadNudge(AssetManager::Node* node) {
	auto source = skillAnimationActors[node->getData()->first_attribute("source")->value()];
	auto destination = skillAnimationActors[node->getData()->first_attribute("destination")->value()];
	float distance = (float)atof(node->getData()->first_attribute("distance")->value());
	return std::unique_ptr<SkillAnimation>(new Nudge(source, destination, distance));
}

std::unique_ptr<SkillAnimation> AssetManager::loadProjectile(AssetManager::Node* node) {
	auto sprite = getSprite(node->getSprite());
	auto source = skillAnimationActors[node->getData()->first_attribute("source")->value()];
	auto destination = skillAnimationActors[node->getData()->first_attribute("destination")->value()];
	auto speed = (float)atof(node->getData()->first_attribute("speed")->value());
	return std::unique_ptr<SkillAnimation>(new Projectile(sprite, source, destination, speed));
}

