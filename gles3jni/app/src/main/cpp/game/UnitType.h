#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Texture.h"

class UnitType {
public:
	UnitType(Texture* texture);
	~UnitType();

private:
	Texture* texture;
};

#endif //GLES3JNI_UNITTYPE_H
