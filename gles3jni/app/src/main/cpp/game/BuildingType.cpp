#include "BuildingType.h"

BuildingType::BuildingType(Sprite* sprite, std::string name, std::string description, std::vector<std::pair<Resource*, int>> resourceProductions, std::vector<Recruitment> recruitments) {
	this->sprite = sprite;
	this->name = name;
	this->description = description;
	this->resourceProductions = resourceProductions;
	this->recruitments = recruitments;
}

BuildingType::~BuildingType() {

}

Recruitment::Recruitment(UnitType* unitType, int time, std::vector<ResourceAmount> resourceCosts) {
	this->unitType = unitType;
	this->time = time;
	this->resourceCosts = resourceCosts;
}
