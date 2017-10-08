#include "Sprite.h"

Sprite::Sprite(Texture* texture, int x, int y, int w, int h) {
	this->texture = texture;

	auto left = w / -2;
	auto top = h / 2;
	auto right = left + w;
	auto bottom = top - h;
	auto textureLeft = (float)x / texture->getWidth();
	auto textureTop = (float)y / texture->getHeight();
	auto textureRight = textureLeft + (float)w / texture->getWidth();
	auto textureBottom = textureTop + (float)h / texture->getHeight();

	std::vector<Vertex> vertices(4);
	vertices[0] = {{left, top}, {textureLeft, textureTop}};
	vertices[1] = {{right, top}, {textureRight, textureTop}};
	vertices[2] = {{left, bottom}, {textureLeft, textureBottom}};
	vertices[3] = {{right, bottom}, {textureRight, textureBottom}};

	std::vector<uint16_t> indices = {0, 2, 1, 1, 2, 3};

	mesh = std::unique_ptr<Mesh>(new Mesh(vertices, indices));
}
