#ifndef GLES3JNI_HEXTYPE_H
#define GLES3JNI_HEXTYPE_H

#include "Texture.h"

class HexType {
public:
	HexType(Texture* texture);
	~HexType();

private:
    Texture* texture;
};

#endif //GLES3JNI_HEXTYPE_H
