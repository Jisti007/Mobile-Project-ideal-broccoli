#ifndef GLES3JNI_MESH_H
#define GLES3JNI_MESH_H

#include <vector>
#include "../glm/glm.hpp"
#include <GLES3/gl3.h>
//#include "../gl3stub.h"

struct Vertex {
public:
	glm::vec2 position;
	glm::vec2 texture;

	Vertex();
	Vertex(glm::vec2 position, glm::vec2 texture);

	static void enableAttributes();
};

class Mesh {
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
	~Mesh();

	void initialize(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
	void reload();
	void destroy();
	void deleteBuffer(GLuint* buffer);

	inline const GLuint getVertexArray() const { return vertexArray; }
	inline const size_t getIndexCount() const { return indices.size(); }

private:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint indexBuffer;
};

#endif //GLES3JNI_MESH_H
