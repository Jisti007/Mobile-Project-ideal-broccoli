#include "Faction.h"

Faction::Faction(std::vector<glm::vec3> colors) {
	this->colors = colors;
}

Faction::~Faction() {

}

bool Faction::modifyResource(Resource* resource, int amount) {
	if (resources[resource] + amount < 0) {
		return false;
	}
	resources[resource] += amount;
	return true;
}

bool Faction::modifyResource(ResourceAmount amount) {
	return modifyResource(amount.first, amount.second);
}
