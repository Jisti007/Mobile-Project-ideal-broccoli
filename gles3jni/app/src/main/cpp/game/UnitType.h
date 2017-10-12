#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Sprite.h"

class UnitType {
public:
	UnitType(Sprite* sprite);
	~UnitType();

	inline Sprite* getSprite() const { return sprite; }

private:
	Sprite* sprite;
};

#endif //GLES3JNI_UNITTYPE_H
