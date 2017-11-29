//
// Created by K1697 on 29.11.2017.
//

#include "RecoloredUISprite.h"

RecoloredUISprite::RecoloredUISprite(Sprite* sprite, glm::vec2 position,
	std::vector<glm::vec3> destinationColors) : UISprite(sprite, position) {
	this->destinationColors = destinationColors;
}

RecoloredUISprite::RecoloredUISprite(Sprite* sprite, glm::vec2 position,
	glm::vec2 size, std::vector<glm::vec3> destinationColors) : UISprite(sprite, position, size) {
	this->destinationColors = destinationColors;
}

RecoloredUISprite::RecoloredUISprite(Sprite* sprite, glm::vec2 position,
	float scale, std::vector<glm::vec3> destinationColors) : UISprite(sprite, position, scale) {
	this->destinationColors = destinationColors;
}

RecoloredUISprite::RecoloredUISprite(Sprite* sprite, glm::vec2 position,
	glm::vec2 size, float scale, std::vector<glm::vec3> destinationColors)
	: UISprite(sprite, position, size, scale) {
	this->destinationColors = destinationColors;
}

void RecoloredUISprite::onDraw(Pipeline* pipeline) {
	pipeline->draw(getSprite(), getPosition(), getScale(), destinationColors);
}

RecoloredUISprite::~RecoloredUISprite() {

}
