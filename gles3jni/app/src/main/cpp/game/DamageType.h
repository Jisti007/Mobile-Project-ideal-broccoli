#ifndef GLES3JNI_DAMAGETYPE_H
#define GLES3JNI_DAMAGETYPE_H

#include "Sprite.h"

class DamageType {
public:
	DamageType(const char* name, Sprite* sprite);

	inline const char* getName() const { return name.c_str(); }
	inline const Sprite* getSprite() const { return sprite; }

private:
	std::string name;
	Sprite* sprite;
};

#endif //GLES3JNI_DAMAGETYPE_H
