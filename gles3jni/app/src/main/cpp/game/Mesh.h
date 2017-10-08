#ifndef GLES3JNI_MESH_H
#define GLES3JNI_MESH_H

#include <vector>
#include "../glm/vec2.hpp"
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
	Mesh(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
	~Mesh();

	inline const GLuint getVertexArray() const { return vertexArray; }
	inline const size_t getIndexCount() const { return indexCount; }

private:
	//std::vector<Vertex> vertices;
	//std::vector<uint16_t> indices;
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	size_t indexCount;
};

#endif //GLES3JNI_MESH_H
