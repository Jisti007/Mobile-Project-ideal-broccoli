#ifndef GLES3JNI_BUILDINGTYPE_H
#define GLES3JNI_BUILDINGTYPE_H

#include "Sprite.h"
#include "Resource.h"

class BuildingType {
public:
	BuildingType(Sprite* sprite, std::vector<ResourceAmount> resourceProductions);
	~BuildingType();

	inline Sprite* getSprite() const { return sprite; }
	inline const std::vector<ResourceAmount> getResourceProductions() const { return resourceProductions; }

private:
	Sprite* sprite;
	std::vector<ResourceAmount> resourceProductions;
};

#endif //GLES3JNI_BUILDINGTYPE_H
