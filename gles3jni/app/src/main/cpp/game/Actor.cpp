#include "Actor.h"

Actor::Actor(Scene* scene, Texture* texture, Mesh* mesh, glm::vec2 position) {
	this->scene = scene;
	this->mesh = mesh;
	this->texture = texture;
	this->position = position;
}

Actor::~Actor() {

}

void Actor::remove() {
	scene->removeActor(this);
}
