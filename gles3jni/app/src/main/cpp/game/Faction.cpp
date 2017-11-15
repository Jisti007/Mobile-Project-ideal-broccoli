#include "Faction.h"

Faction::Faction(std::vector<glm::vec3> colors) {
	this->colors = colors;
}

Faction::~Faction() {

}

void Faction::addResource(const Resource* resource, int amount) {
	resources[resource] = amount;
}
