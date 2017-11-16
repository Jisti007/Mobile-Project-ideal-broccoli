#ifndef GLES3JNI_RESOURCETYPE_H
#define GLES3JNI_RESOURCETYPE_H

#include "Texture.h"
#include "Sprite.h"

class Resource {
public:
	Resource(Sprite* sprite, int priority);
	~Resource();

	inline Sprite* getSprite() { return sprite; }

private:
	Sprite* sprite;
	int priority;
};

#endif //GLES3JNI_RESOURCETYPE_H
