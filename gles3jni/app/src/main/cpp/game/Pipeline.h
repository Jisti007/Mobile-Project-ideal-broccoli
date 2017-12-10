#ifndef GLES3JNI_PIPELINE_H
#define GLES3JNI_PIPELINE_H

#include <GLES3/gl3.h>
#include "../glm/glm.hpp"
#include "Sprite.h"
#include "Rectangle.h"
#include "Camera.h"

class Pipeline {
public:
	Pipeline();
	~Pipeline();

	void initialize();
	void destroy();
	void beginDraw();
	void draw(
		Sprite* sprite, glm::vec2 position, glm::vec2 scale = {1.0f, 1.0f},
		glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f}
	);
	void draw(
		Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors,
		glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f}
	);
	void draw(
		Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors,
		glm::vec2 scale, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f}
	);
	void endDraw();
	void setAmbientColor(glm::vec3 color);
	void setCameraPosition(glm::vec2 position);
	void setCameraZoom(float zoom);
	void setViewportSize(int width, int height);
	bool isVisible(Rectangle rectangle);

	inline GLuint getProgram() { return program; }
	inline Rectangle getViewport() { return Rectangle(viewportSize / -2.0f, viewportSize); }

private:
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint lastTexture = 0;
	GLuint lastVertexArray = 0;
	GLint ambientColorLocation;
	GLint instanceColorLocation;
	GLint instancePositionLocation;
	GLint instanceScaleLocation;
	GLint sourceColorsLocation;
	GLint destinationColorsLocation;
	GLint numberOfColorSwapsLocation;
	glm::vec2 viewportSize;
	glm::vec2 cameraPosition;
	float cameraZoom;

	void draw(
		Sprite* sprite, glm::vec2 position, GLint numberOfColorSwaps,
		glm::vec2 scale = {1.0f, 1.0f}, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f}
	);
	GLuint createShader(const char* source, GLenum type);
	void deleteShader(GLuint* shader);
};

#endif //GLES3JNI_PIPELINE_H
