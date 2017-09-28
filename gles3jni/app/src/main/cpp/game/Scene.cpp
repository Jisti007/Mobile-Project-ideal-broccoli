#include <algorithm>
#include "Scene.h"

using namespace std;

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
/*
GLuint shaderProgram;

GLuint createShader(const char* source, GLenum type) {
	int success;
	char log[512];
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, log);
	}
	glAttachShader(shaderProgram, shader);
	return shader;
}

void Scene::initializePipeline() {
	int success;
	char log[512];
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shaderProgram = glCreateProgram();
	createShader(vertexSource, GL_VERTEX_SHADER);
	createShader(fragmentSource, GL_FRAGMENT_SHADER);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
	}
}
*/

void Scene::initialize(Pipeline* pipeline) {
	this->pipeline = pipeline;
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

	glUseProgram(pipeline->getProgram());
	Vertex::enableAttributes();
	auto instancePositionLocation = glGetUniformLocation(pipeline->getProgram(), "instancePosition");

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
