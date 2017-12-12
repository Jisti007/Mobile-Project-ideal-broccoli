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

bool Faction::subtractResource(ResourceAmount amount) {
	return modifyResource(ResourceAmount{amount.first, -amount.second});
}

bool Faction::modifyResources(std::vector<ResourceAmount>& resourceAmounts) {
	for (auto resourceAmount : resourceAmounts) {
		modifyResource(resourceAmount);
	}
}

bool Faction::hasResources(std::vector<ResourceAmount>& resourceAmounts) {
	for (auto& resourceAmount : resourceAmounts) {
		if (!hasResource(resourceAmount)) {
			return false;
		}
	}

	return true;
}

bool Faction::hasResources(const std::vector<ResourceAmount>& resourceAmounts) {
	for (auto& resourceAmount : resourceAmounts) {
		if (!hasResource(resourceAmount)) {
			return false;
		}
	}

	return true;
}
