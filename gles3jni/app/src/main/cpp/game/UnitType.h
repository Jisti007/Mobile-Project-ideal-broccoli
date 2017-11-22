#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Sprite.h"

class UnitType {
public:
	UnitType(Sprite* sprite, int hp);
	~UnitType();

	inline Sprite* getSprite() const { return sprite; }
	inline int getHP() { return hp; }

private:
	Sprite* sprite;
	int hp;
};

#endif //GLES3JNI_UNITTYPE_H
