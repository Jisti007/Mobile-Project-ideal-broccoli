#include "Sprite.h"
/*
Sprite::Sprite(Texture* texture, Mesh* mesh) {
	this->texture = texture;
	this->mesh = mesh;
}
*/
Sprite::Sprite(Texture* texture, int x, int y, int w, int h) {
	this->texture = texture;

	auto left = x - w / 2;
	auto top = y + h / 2;
	auto right = left + w;
	auto bottom = top - h;

	std::vector<Vertex> vertices(4);
	vertices[0] = {{left, top}, {0.0f, 0.0f}};
	vertices[1] = {{right, top}, {1.0f, 0.0f}};
	vertices[2] = {{left, bottom}, {0.0f, 1.0f}};
	vertices[3] = {{right, bottom}, {1.0f, 1.0f}};

	std::vector<uint16_t> indices = {0, 2, 1, 1, 2, 3};
	/*
	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;
	*/

	mesh = std::unique_ptr<Mesh>(new Mesh(vertices, indices));
}
