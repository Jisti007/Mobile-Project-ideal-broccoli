#include <algorithm>
#include "Scene.h"

using namespace std;

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
	outColor = texture(sampler, fragmentTexture).rgba;
}
)glsl";

Scene::Scene() {

}

Scene::~Scene() {
	for (const auto textureActors : actors) {
		for (const auto meshActors : textureActors.second) {
			for (auto actor : meshActors.second) {
				delete actor;
			}
		}
	}
}

GLuint shaderProgram;

GLuint createShader(const char* source, GLenum type) {
	int success;
	char log[512];
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderInfoLog(shader, 512, NULL, log);
	glAttachShader(shaderProgram, shader);
	return shader;
}

void Scene::initializePipeline() {
	int success;
	char log[512];
	shaderProgram = glCreateProgram();
	createShader(vertexSource, GL_VERTEX_SHADER);
	createShader(fragmentSource, GL_FRAGMENT_SHADER);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
	}
}

Actor* Scene::addActor(Sprite* sprite, glm::vec2 position) {
	return addActor(sprite->getTexture(), sprite->getMesh(), position);
}

Actor* Scene::addActor(Texture* texture, Mesh* mesh, glm::vec2 position) {
	auto actor = new Actor(this, texture, mesh, position);
	actors[texture][mesh].push_back(actor);
	return actor;
}

void Scene::removeActor(Actor* actor) {
	removedActors.push_back(actor);
}

void Scene::draw() {
	destroyActors();

	glUseProgram(shaderProgram);
	//Vertex::enableAttributes();
	auto instancePositionLocation = glGetUniformLocation(shaderProgram, "instancePosition");

	for (const auto textureActors : actors) {
		glBindTexture(GL_TEXTURE_2D, textureActors.first->getHandle());

		for (const auto meshActors : textureActors.second) {
			auto mesh = meshActors.first;
			glBindVertexArray(meshActors.first->getVertexArray());

			for (const auto actor : meshActors.second) {
				glUniform2f(instancePositionLocation, actor->getX(), actor->getY());
				glDrawElements(GL_TRIANGLES, (GLsizei) mesh->getIndexCount(), GL_UNSIGNED_SHORT, 0);
			}
		}
	}
}

void Scene::destroyActors() {
	for (auto actor : removedActors) {
		auto actorGroup = actors[actor->getTexture()][actor->getMesh()];
		auto position = std::find(actorGroup.begin(), actorGroup.end(), actor);
		if (position != actorGroup.end()) {
			actorGroup.erase(position);
			delete actor;
		}
	}
}
