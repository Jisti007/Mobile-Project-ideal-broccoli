#ifndef GLES3JNI_RESOURCETYPE_H
#define GLES3JNI_RESOURCETYPE_H

#include "Texture.h"

class Resource {
public:
	Resource(Texture* texture);
	~Resource();

private:
	Texture* texture;
};

#endif //GLES3JNI_RESOURCETYPE_H
