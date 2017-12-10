#include "Pipeline.h"
#include "Rectangle.h"

const char* vertexSource = R"glsl(#version 300 es
precision highp float;
precision highp int;
precision lowp sampler2D;
precision lowp samplerCube;

uniform vec2 cameraSize;
uniform vec2 cameraPosition;
uniform vec2 instancePosition;
uniform vec2 instanceScale;

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexTexture;

out vec2 fragmentTexture;

void main(){
	vec2 position = vertexPosition;
	position.x *= instanceScale.x;
	position.y *= instanceScale.y;
	position += instancePosition - cameraPosition;
	position.x = position.x / cameraSize.x;
	position.y = position.y / cameraSize.y;

	gl_Position = vec4(position, 0.0, 1.0);
	fragmentTexture = vertexTexture;
}
)glsl";

const char* fragmentSource = R"glsl(#version 300 es

precision mediump int;
precision lowp sampler2D;
precision lowp samplerCube;
precision mediump float;

const int MAX_COLOR_SWAPS = 4;
const float COLOR_SWAP_TOLERANCE = 0.25 / 255.0;

uniform sampler2D sampler;
uniform vec4 instanceColor;
uniform vec3 ambientColor;
uniform vec3 sourceColors[MAX_COLOR_SWAPS];
uniform vec3 destinationColors[MAX_COLOR_SWAPS];
uniform int numberOfColorSwaps;

in vec2 fragmentTexture;

layout(location = 0) out vec4 outColor;

void main(){
	outColor = texture(sampler, fragmentTexture);
	for (int i = 0; i < numberOfColorSwaps; i++) {
		float dr = abs(outColor.r - sourceColors[i].r);
		float dg = abs(outColor.g - sourceColors[i].g);
		float db = abs(outColor.b - sourceColors[i].b);
		if (dr < COLOR_SWAP_TOLERANCE && dg < COLOR_SWAP_TOLERANCE && db < COLOR_SWAP_TOLERANCE) {
			outColor.rgb = destinationColors[i];
			break;
		}
	}

	outColor *= instanceColor * vec4(ambientColor, 1.0);
}
)glsl";

Pipeline::Pipeline() {

}

Pipeline::~Pipeline() {
	destroy();
}

void Pipeline::initialize() {
	destroy();

	int success;
	char log[512];
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	program = glCreateProgram();
	vertexShader = createShader(vertexSource, GL_VERTEX_SHADER);
	fragmentShader = createShader(fragmentSource, GL_FRAGMENT_SHADER);
	glLinkProgram(program);
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, log);
	}

	ambientColorLocation = glGetUniformLocation(getProgram(), "ambientColor");
	instanceColorLocation = glGetUniformLocation(getProgram(), "instanceColor");
	instancePositionLocation = glGetUniformLocation(getProgram(), "instancePosition");
	instanceScaleLocation = glGetUniformLocation(getProgram(), "instanceScale");
	sourceColorsLocation = glGetUniformLocation(getProgram(), "sourceColors");
	destinationColorsLocation = glGetUniformLocation(getProgram(), "destinationColors");
	numberOfColorSwapsLocation = glGetUniformLocation(getProgram(), "numberOfColorSwaps");
}

void Pipeline::destroy() {
	deleteShader(&fragmentShader);
	deleteShader(&vertexShader);
	if (program && glIsProgram(program)) {
		glDeleteProgram(program);
		program = 0;
	}
}

void Pipeline::beginDraw() {
	glUseProgram(getProgram());
	Vertex::enableAttributes();
	setAmbientColor({1.0f, 1.0f, 1.0f});
}

void Pipeline::draw(Sprite* sprite, glm::vec2 position, glm::vec2 scale, glm::vec4 color) {
	draw(sprite, position, 0, scale, color);
}

void Pipeline::draw(
	Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors, glm::vec4 color
) {
	draw(sprite, position, destinationColors, glm::vec2(1.0f, 1.0f), color);
}

void Pipeline::draw(
	Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors,
	glm::vec2 scale, glm::vec4 color
) {
	auto numberOfColorSwaps = (GLint)std::min(
		sprite->getSwappableColors().size(), destinationColors.size()
	);
	glUniform3fv(
		sourceColorsLocation,
		(GLsizei)numberOfColorSwaps,
		(GLfloat*)sprite->getSwappableColors().data()
	);
	glUniform3fv(
		destinationColorsLocation,
		(GLsizei)numberOfColorSwaps,
		(GLfloat*)destinationColors.data()
	);

	draw(sprite, position, numberOfColorSwaps, scale, color);
}

void Pipeline::endDraw() {
	glUniform1i(numberOfColorSwapsLocation, (GLint)0);
	glActiveTexture(GL_TEXTURE0);
	lastTexture = 0;
	glBindTexture(GL_TEXTURE_2D, lastTexture);
	lastVertexArray = 0;
	glBindVertexArray(lastVertexArray);
	glUseProgram(0);
}

void Pipeline::setAmbientColor(glm::vec3 color) {
	glUniform3f(ambientColorLocation, color.r, color.g, color.b);
}

void Pipeline::setCameraPosition(glm::vec2 position) {
	this->cameraPosition = position;
	auto cameraPositionLocation = glGetUniformLocation(getProgram(), "cameraPosition");
	glUniform2f(cameraPositionLocation, position.x, position.y);
}

void Pipeline::setCameraZoom(float zoom) {
	this->cameraZoom = zoom;
	auto cameraSizeLocation = glGetUniformLocation(getProgram(), "cameraSize");
	glUniform2f(cameraSizeLocation, viewportSize.x / 2.0f / zoom, viewportSize.y / 2.0f / zoom);
}

void Pipeline::setViewportSize(int width, int height) {
	viewportSize = { width, height };
	glViewport(0, 0, width, height);
}

bool Pipeline::isVisible(Rectangle rectangle) {
	Rectangle viewportBounds(
		cameraPosition - viewportSize / 2.0f / cameraZoom,
		viewportSize / cameraZoom
	);
	return viewportBounds.overlaps(rectangle);
}

void Pipeline::draw(
	Sprite* sprite, glm::vec2 position, GLint numberOfColorSwaps,
	glm::vec2 scale, glm::vec4 color
) {
	glUniform1i(numberOfColorSwapsLocation, numberOfColorSwaps);
	glUniform4f(instanceColorLocation, color.r, color.g, color.b, color.a);
	glUniform2f(instancePositionLocation, position.x, position.y);
	glUniform2f(instanceScaleLocation, scale.x, scale.y);
	auto texture = sprite->getTexture()->getHandle();
	if (texture != lastTexture) {
		glBindTexture(GL_TEXTURE_2D, texture);
		lastTexture = texture;
	}
	auto mesh = sprite->getMesh();
	auto vertexArray = mesh->getVertexArray();
	if (vertexArray != lastVertexArray) {
		glBindVertexArray(vertexArray);
		lastVertexArray = vertexArray;
	}

	glDrawElements(GL_TRIANGLES, (GLsizei) mesh->getIndexCount(), GL_UNSIGNED_SHORT, 0);
}

GLuint Pipeline::createShader(const char* source, GLenum type) {
	int success;
	char log[512];
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, log);
	}
	glAttachShader(program, shader);
	return shader;
}

void Pipeline::deleteShader(GLuint* shader) {
	if (*shader && glIsShader(*shader)) {
		glDeleteShader(*shader);
		*shader = 0;
	}
}
