#ifndef GLES3JNI_PIPELINE_H
#define GLES3JNI_PIPELINE_H

#include <GLES3/gl3.h>
#include "../glm/glm.hpp"
#include "Sprite.h"
#include "Rectangle.h"

class Pipeline {
public:
	Pipeline();
	~Pipeline();

	void initialize();
	void destroy();
	void beginDraw();
	void draw(Sprite* sprite, glm::vec2 position);
	void draw(Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors);
	void endDraw();
	void setCameraPosition(glm::vec2 position);
	void setViewportSize(int width, int height);

	inline GLuint getProgram() { return program; }
	inline Rectangle getViewport() { return Rectangle(viewportSize / -2.0f, viewportSize); }

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
	glm::vec2 cameraPosition;
	glm::vec2 viewportSize;

	GLuint createShader(const char* source, GLenum type);
	void deleteShader(GLuint* shader);
};

#endif //GLES3JNI_PIPELINE_H
