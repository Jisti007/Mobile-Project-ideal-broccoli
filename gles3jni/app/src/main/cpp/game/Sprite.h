#ifndef GLES3JNI_SPRITE_H
#define GLES3JNI_SPRITE_H

#include <memory>
#include "Texture.h"
#include "Mesh.h"

class Sprite {
public:
	Sprite(Texture* texture, int x, int y, int w, int h);

	inline Texture* getTexture() const { return texture; }
	inline Mesh* getMesh() const { return mesh.get(); }

private:
	Texture* texture;
	std::unique_ptr<Mesh> mesh;
};

#endif //GLES3JNI_SPRITE_H
