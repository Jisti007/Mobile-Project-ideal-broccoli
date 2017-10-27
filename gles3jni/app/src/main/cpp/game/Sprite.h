#ifndef GLES3JNI_SPRITE_H
#define GLES3JNI_SPRITE_H

#include <memory>
#include "Texture.h"
#include "Mesh.h"
#include "../glm/vec3.hpp"

class Sprite {
public:
	Sprite(const char* id, Texture* texture, int x, int y, int w, int h, int xOffset, int yOffset, std::vector<glm::vec3> swappableColors);

	void createMesh();

	inline Texture* getTexture() const { return texture; }
	inline Mesh* getMesh() const { return mesh.get(); }
	inline const std::vector<glm::vec3>& getSwappableColors() const { return swappableColors; }

private:
	std::string id;
	Texture* texture;
	std::unique_ptr<Mesh> mesh;
	std::vector<glm::vec3> swappableColors;
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};

#endif //GLES3JNI_SPRITE_H
