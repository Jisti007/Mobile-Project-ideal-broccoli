#ifndef GLES3JNI_BUILDINGTYPE_H
#define GLES3JNI_BUILDINGTYPE_H

#include "Sprite.h"
#include "Resource.h"

class BuildingType {
public:
	BuildingType(Sprite* sprite, std::string name, std::string description, std::vector<ResourceAmount> resourceProductions);
	~BuildingType();

	inline Sprite* getSprite() const { return sprite; }
	inline const std::vector<ResourceAmount> getResourceProductions() const { return resourceProductions; }
	inline const std::string getName() const { return name; };
	inline const std::string getDescription() const { return description; };

private:
	Sprite* sprite;
	std::string name, description;
	std::vector<ResourceAmount> resourceProductions;
};

#endif //GLES3JNI_BUILDINGTYPE_H
