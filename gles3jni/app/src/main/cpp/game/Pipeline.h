#ifndef GLES3JNI_PIPELINE_H
#define GLES3JNI_PIPELINE_H

#include <GLES3/gl3.h>
#include "../glm/glm.hpp"
#include "Sprite.h"

class Pipeline {
public:
	Pipeline();
	~Pipeline();

	void initialize();
	void destroy();
	inline GLuint getProgram() { return program; }
	void beginDraw(glm::vec2 position, glm::vec2 size);
	void draw(Sprite* sprite, glm::vec2 position);
	void draw(Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors);
	void endDraw();

private:
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint lastTexture = 0;
	GLuint lastVertexArray = 0;
	GLint instancePositionLocation;
	GLint sourceColorsLocation;
	GLint destinationColorsLocation;
	GLint numberOfColorSwapsLocation;

	GLuint createShader(const char* source, GLenum type);
	void deleteShader(GLuint* shader);
};

#endif //GLES3JNI_PIPELINE_H
