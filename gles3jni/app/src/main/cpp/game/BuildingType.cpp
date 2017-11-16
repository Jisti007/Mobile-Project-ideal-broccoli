#include "BuildingType.h"

BuildingType::BuildingType(Sprite* sprite, std::vector<std::pair<Resource*, int>> resourceProductions) {
	this->sprite = sprite;
	this->resourceProductions = resourceProductions;
}

BuildingType::~BuildingType() {

}
