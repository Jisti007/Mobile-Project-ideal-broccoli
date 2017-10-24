#ifndef GLES3JNI_SPRITE_H
#define GLES3JNI_SPRITE_H

#include <memory>
#include "Texture.h"
#include "Mesh.h"
#include "../glm/vec3.hpp"

class Sprite {
public:
	Sprite(Texture* texture, int x, int y, int w, int h, int xOffset, int yOffset, std::vector<glm::vec3> swappableColors);

	inline Texture* getTexture() const { return texture; }
	inline Mesh* getMesh() const { return mesh.get(); }
	inline std::vector<glm::vec3> getSwappableColors() { return swappableColors; }

private:
	Texture* texture;
	std::unique_ptr<Mesh> mesh;
	std::vector<glm::vec3> swappableColors;
};

#endif //GLES3JNI_SPRITE_H
