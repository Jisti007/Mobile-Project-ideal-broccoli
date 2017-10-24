#ifndef GLES3JNI_RESOURCETYPE_H
#define GLES3JNI_RESOURCETYPE_H

#include "Texture.h"
#include "Sprite.h"

class Resource {
public:
	Resource(Sprite* sprite);
	~Resource();

private:
	Sprite* sprite;
};

#endif //GLES3JNI_RESOURCETYPE_H
