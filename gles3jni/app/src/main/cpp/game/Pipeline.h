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
	void draw(Sprite* sprite, glm::vec2 position, float scale = 1.0f);
	void draw(Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors);
	void endDraw();
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
	GLint instancePositionLocation;
	GLint instanceScaleLocation;
	GLint sourceColorsLocation;
	GLint destinationColorsLocation;
	GLint numberOfColorSwapsLocation;
	glm::vec2 viewportSize;
	glm::vec2 cameraPosition;
	float cameraZoom;

	GLuint createShader(const char* source, GLenum type);
	void deleteShader(GLuint* shader);
};

#endif //GLES3JNI_PIPELINE_H
