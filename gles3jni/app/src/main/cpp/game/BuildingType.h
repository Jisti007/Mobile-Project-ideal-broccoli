#ifndef GLES3JNI_BUILDINGTYPE_H
#define GLES3JNI_BUILDINGTYPE_H

#include "Sprite.h"

class BuildingType {
public:
	BuildingType(Sprite* sprite);
	~BuildingType();

	inline Sprite* getSprite() const { return sprite; }

private:
	Sprite* sprite;
};

#endif //GLES3JNI_BUILDINGTYPE_H
