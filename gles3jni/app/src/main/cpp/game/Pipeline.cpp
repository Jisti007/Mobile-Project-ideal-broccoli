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
    vec2 position = vertexPosition + instancePosition + cameraPosition;
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

uniform sampler2D sampler;

in vec2 fragmentTexture;

layout(location = 0) out vec4 outColor;

void main(){
	outColor = texture(sampler, fragmentTexture);
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
}

void Pipeline::destroy() {
	if (program) {
		glDeleteProgram(program);
		program = NULL;
	}
	if (vertexShader) {
		glDeleteShader(vertexShader);
		vertexShader = NULL;
	}
	if (fragmentShader) {
		glDeleteShader(fragmentShader);
		fragmentShader = NULL;
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

void Pipeline::beginRender(glm::vec2 position, glm::vec2 size) {
	glUseProgram(getProgram());
	Vertex::enableAttributes();
	auto cameraPositionLocation = glGetUniformLocation(getProgram(), "cameraPosition");
	auto cameraSizeLocation = glGetUniformLocation(getProgram(), "cameraSize");
	glUniform2f(cameraPositionLocation, position.x, position.y);
	glUniform2f(cameraSizeLocation, size.x, size.y);
}

void Pipeline::render(Sprite *sprite, glm::vec2 position) {
	glUniform2f(instancePositionLocation, position.x, position.y);
	glBindTexture(GL_TEXTURE_2D, sprite->getTexture()->getHandle());
	auto mesh = sprite->getMesh();
	glBindVertexArray(mesh->getVertexArray());
	glDrawElements(GL_TRIANGLES, (GLsizei) mesh->getIndexCount(), GL_UNSIGNED_SHORT, 0);
}

void Pipeline::endRender() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindVertexArray(NULL);
	glUseProgram(NULL);
}

