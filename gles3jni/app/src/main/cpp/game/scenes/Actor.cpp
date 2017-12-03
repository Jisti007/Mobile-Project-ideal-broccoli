#include "Actor.h"

Actor::Actor(Sprite* sprite, glm::vec2 position, float depth, int layer) {
	this->sprite = sprite;
	this->position = position;
	this->depth = depth;
	this->layer = layer;
}

void Actor::draw(Pipeline* pipeline) {
	pipeline->draw(sprite, position, 1.0f);
}

