#ifndef GLES3JNI_FACTION_H
#define GLES3JNI_FACTION_H

class Building;

#include <vector>
#include <unordered_map>
#include "../glm/glm.hpp"
#include "Resource.h"

class Faction {
public:
	Faction(std::vector<glm::vec3> colors);
	~Faction();

	bool modifyResource(Resource* resource, int amount);
	bool modifyResource(ResourceAmount amount);

	inline const std::unordered_map<Resource*, int> getResources() const { return resources; }
	//inline const std::vector<Building*>& getBuildings() { return buildings; };
	inline const std::vector<glm::vec3> getColors() const { return colors; }
	inline bool isPlayer() { return player; }
	inline void setPlayer(bool player) { this->player = player; }

private:
	std::vector<glm::vec3> colors;
	//std::vector<Building*> buildings;
	std::unordered_map<Resource*, int> resources;
	bool player = false;
};

#endif //GLES3JNI_FACTION_H
