#ifndef GLES3JNI_SPRITE_H
#define GLES3JNI_SPRITE_H

#include <memory>
#include "Texture.h"
#include "Mesh.h"
#include "../glm/glm.hpp"

class Sprite {
public:
	Sprite(const char* id, Texture* texture, int x, int y, int w, int h, int xOffset, int yOffset, std::vector<glm::vec3> swappableColors);

	inline void reload() { mesh.reload(); }
	inline Texture* getTexture() const { return texture; }
	inline Mesh* getMesh() { return &mesh; }
	inline const std::vector<glm::vec3>& getSwappableColors() const { return swappableColors; }
	inline int getWidth(){ return width; }
	inline int getHeight(){ return height; }


private:
	std::string id;
	Texture* texture;
	Mesh mesh;
	std::vector<glm::vec3> swappableColors;
	//std::vector<Vertex> vertices;
	//std::vector<uint16_t> indices;
	int width;
	int height;
};

#endif //GLES3JNI_SPRITE_H
