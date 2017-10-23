#ifndef GLES3JNI_PIPELINE_H
#define GLES3JNI_PIPELINE_H

#include <GLES3/gl3.h>
#include "../glm/vec2.hpp"
#include "Sprite.h"

class Pipeline {
public:
	Pipeline();
	~Pipeline();

	void initialize();
	void destroy();
	inline GLuint getProgram() { return program; }
	void beginRender(glm::vec2 position, glm::vec2 size);
	void render(Sprite* sprite, glm::vec2 position);
	void endRender();

private:
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint lastTexture = 0;
	GLuint lastVertexArray = 0;
	GLint instancePositionLocation;

	GLuint createShader(const char* source, GLenum type);
};

#endif //GLES3JNI_PIPELINE_H
