#include "Actor.h"

Actor::Actor(Sprite* sprite, glm::vec2 position, float depth, int layer, bool visible) {
	this->sprite = sprite;
	this->position = position;
	this->depth = depth;
	this->layer = layer;
	this->visible = visible;
}

void Actor::draw(Pipeline* pipeline) {
	pipeline->draw(sprite, position, 1.0f, color);
}

