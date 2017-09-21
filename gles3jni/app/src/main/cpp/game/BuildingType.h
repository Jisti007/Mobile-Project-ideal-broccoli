#ifndef GLES3JNI_BUILDINGTYPE_H
#define GLES3JNI_BUILDINGTYPE_H

#include "Texture.h"

class BuildingType {
public:
	BuildingType(Texture* texture);

	virtual ~BuildingType();

private:
	Texture* texture;
};

#endif //GLES3JNI_BUILDINGTYPE_H
