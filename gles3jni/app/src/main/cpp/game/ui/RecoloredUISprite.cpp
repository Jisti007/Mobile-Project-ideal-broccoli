#include "RecoloredUISprite.h"

RecoloredUISprite::RecoloredUISprite(
	Sprite* sprite, glm::vec2 position, std::vector<glm::vec3> destinationColors
) : UISprite(sprite, position) {
	this->destinationColors = destinationColors;
}

RecoloredUISprite::RecoloredUISprite(
	Sprite* sprite, glm::vec2 position, glm::vec2 size, std::vector<glm::vec3> destinationColors
) : UISprite(sprite, position, size) {
	this->destinationColors = destinationColors;
}

RecoloredUISprite::RecoloredUISprite(
	Sprite* sprite, Transform2D transform, std::vector<glm::vec3> destinationColors
) : UISprite(sprite, transform) {
	this->destinationColors = destinationColors;
}

RecoloredUISprite::RecoloredUISprite(Sprite* sprite, glm::vec2 position,
	glm::vec2 size, glm::vec2 scale, std::vector<glm::vec3> destinationColors
) : UISprite(sprite, position, size, scale) {
	this->destinationColors = destinationColors;
}

void RecoloredUISprite::onDraw(Pipeline* pipeline) {
	pipeline->draw(getSprite(), getPosition(), destinationColors, getScale());
}

RecoloredUISprite::~RecoloredUISprite() {

}
