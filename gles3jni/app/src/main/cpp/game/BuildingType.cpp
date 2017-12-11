#include "BuildingType.h"

BuildingType::BuildingType(Sprite* sprite, std::string name, std::string description, std::vector<std::pair<Resource*, int>> resourceProductions) {
	this->sprite = sprite;
	this->name = name;
	this->description = description;
	this->resourceProductions = resourceProductions;
}

BuildingType::~BuildingType() {

}
