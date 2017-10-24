#include "Sprite.h"

Sprite::Sprite(Texture* texture, int x, int y, int w, int h, int xOffset, int yOffset) {
	this->texture = texture;

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

	mesh = std::unique_ptr<Mesh>(new Mesh(vertices, indices));

	swappableColors.emplace_back(0.0f, 0.0f, 244.0f/255);
}
