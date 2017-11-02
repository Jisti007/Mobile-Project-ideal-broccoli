#ifndef GLES3JNI_HEXTYPE_H
#define GLES3JNI_HEXTYPE_H

#include "Texture.h"
#include "Mesh.h"
#include "Sprite.h"

class HexType {
public:
	HexType(Sprite* sprite, float movementCost);
	~HexType();

	inline Sprite* getSprite() const { return sprite; }
	inline float getMovementCost() { return movementCost; }

private:
	Sprite* sprite;
	float movementCost = 1.0f;
};

#endif //GLES3JNI_HEXTYPE_H
