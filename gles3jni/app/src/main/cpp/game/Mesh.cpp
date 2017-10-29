#include "Mesh.h"

Vertex::Vertex() {

}

Vertex::Vertex(glm::vec2 position, glm::vec2 texture) {
	this->position = position;
	this->texture = texture;
}

void Vertex::enableAttributes() {
	GLuint i = 0;

	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	i++;

	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
}

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
	initialize(vertices, indices);
}

Mesh::~Mesh() {
}

void Mesh::initialize(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
	this->vertices = vertices;
	this->indices = indices;
	reload();
}

void Mesh::reload() {
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);

	Vertex::enableAttributes();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::destroy() {
	deleteBuffer(&vertexBuffer);
	deleteBuffer(&indexBuffer);
	if (vertexArray && glIsVertexArray(vertexArray)) {
		glDeleteVertexArrays(1, &vertexArray);
	}
}

void Mesh::deleteBuffer(GLuint* buffer) {
	if (*buffer && glIsBuffer(*buffer)) {
		glDeleteBuffers(1, buffer);
		*buffer = 0;
	}
}
