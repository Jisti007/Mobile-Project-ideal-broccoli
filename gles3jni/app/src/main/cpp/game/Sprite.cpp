#include "Sprite.h"

Sprite::Sprite(
	const char* id, Texture* texture,
	int x, int y, int w, int h,
	int xOffset, int yOffset,
	std::vector<glm::vec3> swappableColors
) {
	this->id = id;
	this->texture = texture;
	this->width = w;
	this->height = h;

	auto left = w / -2 + xOffset;
	auto top = h / 2 - yOffset;
	auto right = left + w;
	auto bottom = top - h;
	auto textureLeft = (float)x / texture->getWidth();
	auto textureTop = (float)y / texture->getHeight();
	auto textureRight = textureLeft + (float)w / texture->getWidth();
	auto textureBottom = textureTop + (float)h / texture->getHeight();

	std::vector<Vertex> vertices = {
		{{left, top}, {textureLeft, textureTop}},
		{{right, top}, {textureRight, textureTop}},
		{{left, bottom}, {textureLeft, textureBottom}},
		{{right, bottom}, {textureRight, textureBottom}}
	};

	std::vector<uint16_t> indices = {0, 2, 1, 1, 2, 3};

	mesh.initialize(vertices, indices);

	this->swappableColors = swappableColors;
}

Sprite::Sprite(
	const char* id, Texture* texture,
	float width, float height,
	float xOffset, float yOffset,
	float textureLeft, float textureRight,
	float textureTop, float textureBottom,
	std::vector<glm::vec3> swappableColors
) {
	this->id = id;
	this->texture = texture;
	this->width = static_cast<int>(width);
	this->height = static_cast<int>(height);

	auto left = width / -2 + xOffset;
	auto top = height / 2 - yOffset;
	auto right = left + width;
	auto bottom = top - height;

	std::vector<Vertex> vertices = {
		{{left, top}, {textureLeft, textureTop}},
		{{right, top}, {textureRight, textureTop}},
		{{left, bottom}, {textureLeft, textureBottom}},
		{{right, bottom}, {textureRight, textureBottom}}
	};

	std::vector<uint16_t> indices = {0, 2, 1, 1, 2, 3};

	mesh.initialize(vertices, indices);

	this->swappableColors = swappableColors;
}
