#ifndef GLES3JNI_BUILDINGTYPE_H
#define GLES3JNI_BUILDINGTYPE_H

#include "Sprite.h"

class DecorationType {
public:
	DecorationType(Sprite* sprite);
	~DecorationType();

	inline Sprite* getSprite() const { return sprite; }

private:
	Sprite* sprite;
};

#endif //GLES3JNI_BUILDINGTYPE_H
