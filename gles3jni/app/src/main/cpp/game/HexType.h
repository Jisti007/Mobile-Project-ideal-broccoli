#ifndef GLES3JNI_HEXTYPE_H
#define GLES3JNI_HEXTYPE_H

#include "Texture.h"
#include "Mesh.h"
#include "Sprite.h"

class HexType {
public:
	HexType(Sprite* sprite);
	~HexType();

	inline Sprite* getSprite() const { return sprite; }
	//inline const Texture* getTexture() const { return sprite->getTexture(); }
	//inline const Mesh* getMesh() const { return sprite->getMesh(); }

private:
	Sprite* sprite;
};

#endif //GLES3JNI_HEXTYPE_H
