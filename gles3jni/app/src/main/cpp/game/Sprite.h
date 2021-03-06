#ifndef GLES3JNI_SPRITE_H
#define GLES3JNI_SPRITE_H

#include <memory>
#include "Texture.h"
#include "Mesh.h"
#include "../glm/glm.hpp"

class Sprite {
public:
	Sprite(
		const char* id, Texture* texture, int x, int y, int w, int h, int xOffset, int yOffset,
		std::vector<glm::vec3> swappableColors
	);
	Sprite(
		const char* id, Texture* texture,
		float width, float height,
		float xOffset, float yOffset,
		float textureLeft, float textureRight,
		float textureTop, float textureBottom,
		std::vector<glm::vec3> swappableColors
	);

	inline void reload() { mesh.reload(); }
	inline Texture* getTexture() const { return texture; }
	inline Mesh* getMesh() { return &mesh; }
	inline const std::vector<glm::vec3>& getSwappableColors() const { return swappableColors; }
	inline int getWidth(){ return width; }
	inline int getHeight(){ return height; }
	inline glm::vec2 getSize() { return {width, height}; }

private:
	std::string id;
	Texture* texture;
	Mesh mesh;
	std::vector<glm::vec3> swappableColors;
	int width;
	int height;
};

#endif //GLES3JNI_SPRITE_H
