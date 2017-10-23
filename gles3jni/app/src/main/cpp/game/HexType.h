#ifndef GLES3JNI_HEXTYPE_H
#define GLES3JNI_HEXTYPE_H

#include "Texture.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Decoration.h"
#include "WeightedList.h"

class HexType {
public:
	HexType(Sprite* sprite);
	~HexType();

	inline Sprite* getSprite() const { return sprite; }

private:
	Sprite* sprite;
	WeightedList<Decoration*> decorations;
};

#endif //GLES3JNI_HEXTYPE_H
