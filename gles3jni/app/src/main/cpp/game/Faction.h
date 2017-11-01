#ifndef GLES3JNI_FACTION_H
#define GLES3JNI_FACTION_H

#include <vector>
#include "../glm/glm.hpp"

class Faction {
public:
	Faction(std::vector<glm::vec3> colors);
	~Faction();

	inline const std::vector<glm::vec3> getColors() const { return colors; }

private:
	std::vector<glm::vec3> colors;
};

#endif //GLES3JNI_FACTION_H
