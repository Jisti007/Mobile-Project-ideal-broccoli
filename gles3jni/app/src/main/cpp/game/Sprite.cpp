#include "Sprite.h"

Sprite::Sprite(Texture* texture, int x, int y, int w, int h, int xoffset, int yoffset) {
	this->texture = texture;

	auto left = w / -2 + xoffset;
	auto top = h / 2 - yoffset;
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

	mesh = std::unique_ptr<Mesh>(new Mesh(vertices, indices));
}
