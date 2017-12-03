#include "RecoloredActor.h"

RecoloredActor::RecoloredActor(
	Sprite* sprite, glm::vec2 position, float depth, int layer, std::vector<glm::vec3> colors
) : Actor(sprite, position, depth, layer) {
	this->colors = colors;
}

void RecoloredActor::draw(Pipeline* pipeline) {
	pipeline->draw(getSprite(), getPosition(), colors);
}
