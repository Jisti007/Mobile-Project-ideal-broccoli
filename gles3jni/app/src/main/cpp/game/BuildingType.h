#ifndef GLES3JNI_BUILDINGTYPE_H
#define GLES3JNI_BUILDINGTYPE_H

#include "Sprite.h"
#include "Resource.h"

class BuildingType {
public:
	BuildingType(Sprite* sprite, std::vector<std::pair<Resource*, int>> resourceProductions);
	~BuildingType();

	inline Sprite* getSprite() const { return sprite; }

private:
	Sprite* sprite;
	std::vector<std::pair<Resource*, int>> resourceProductions;
};

#endif //GLES3JNI_BUILDINGTYPE_H
