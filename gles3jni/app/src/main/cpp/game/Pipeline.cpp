#include "Pipeline.h"

const char* vertexSource = R"glsl(#version 300 es
precision highp float;
precision highp int;
precision lowp sampler2D;
precision lowp samplerCube;

uniform vec2 cameraSize;
uniform vec2 cameraPosition;
uniform vec2 instancePosition;

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexTexture;

out vec2 fragmentTexture;

void main(){
    vec2 position = vertexPosition + instancePosition - cameraPosition;
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
		}
	}
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

	instancePositionLocation = glGetUniformLocation(getProgram(), "instancePosition");
	sourceColorsLocation = glGetUniformLocation(getProgram(), "sourceColors");
	destinationColorsLocation = glGetUniformLocation(getProgram(), "destinationColors");
	numberOfColorSwapsLocation = glGetUniformLocation(getProgram(), "numberOfColorSwaps");
}

void Pipeline::destroy() {
	if (fragmentShader && glIsShader(fragmentShader)) {
		glDeleteShader(fragmentShader);
		fragmentShader = 0;
	}
	if (vertexShader && glIsShader(vertexShader)) {
		glDeleteShader(vertexShader);
		vertexShader = 0;
	}
	if (program && glIsProgram(program)) {
		glDeleteProgram(program);
		program = 0;
	}
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

void Pipeline::beginDraw(glm::vec2 position, glm::vec2 size) {
	glUseProgram(getProgram());
	Vertex::enableAttributes();
	auto cameraPositionLocation = glGetUniformLocation(getProgram(), "cameraPosition");
	auto cameraSizeLocation = glGetUniformLocation(getProgram(), "cameraSize");
	glUniform2f(cameraPositionLocation, position.x, position.y);
	glUniform2f(cameraSizeLocation, size.x, size.y);
}

void Pipeline::draw(Sprite* sprite, glm::vec2 position) {
	glUniform2f(instancePositionLocation, position.x, position.y);
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

void Pipeline::draw(Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors) {
	glUniform3fv(
		sourceColorsLocation,
		(GLsizei)sprite->getSwappableColors().size(),
		(GLfloat*)sprite->getSwappableColors().data()
	);
	glUniform3fv(
		destinationColorsLocation,
		(GLsizei)destinationColors.size(),
		(GLfloat*)destinationColors.data()
	);
	auto numberOfColorSwaps =
		(GLint)std::min(sprite->getSwappableColors().size(), destinationColors.size());
	glUniform1i(numberOfColorSwapsLocation, numberOfColorSwaps);

	draw(sprite, position);
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

