#include "Pipeline.h"

const char* vertexSource = R"glsl(
#version 300 es

uniform vec2 instancePosition;

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexTexture;

out vec2 fragmentTexture;

void main(){
	gl_Position = vec4(instancePosition + vertexPosition, 0.0, 1.0);
	fragmentTexture = vertexTexture;
}
)glsl";

const char* fragmentSource = R"glsl(
#version 300 es

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
}

void Pipeline::destroy() {
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint Pipeline::createShader(const char *source, GLenum type) {
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
