#include "RecoloredActor.h"

RecoloredActor::RecoloredActor(
	Sprite* sprite, glm::vec2 position, float depth, std::vector<glm::vec3> colors
) : Actor(sprite, position, depth) {
	this->colors = colors;
}

void RecoloredActor::draw(Pipeline* pipeline) {
	pipeline->draw(getSprite(), getPosition(), colors);
}
