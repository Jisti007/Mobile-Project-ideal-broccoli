#ifndef GLES3JNI_SPRITE_H
#define GLES3JNI_SPRITE_H

#include "Texture.h"
#include "Mesh.h"

class Sprite {
public:
	Sprite(Texture* texture, Mesh* mesh);

	inline Texture* getTexture() const { return texture; }
	inline Mesh* getMesh() const { return mesh; }

private:
	Texture* texture;
	Mesh* mesh;
};

#endif //GLES3JNI_SPRITE_H
