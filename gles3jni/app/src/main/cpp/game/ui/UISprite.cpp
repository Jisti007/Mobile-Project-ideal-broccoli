#include "UISprite.h"

UISprite::UISprite(Sprite* sprite, glm::vec2 position)
	: UISprite(sprite, position, sprite->getSize()){

}

UISprite::UISprite(Sprite *sprite, glm::vec2 position, glm::vec2 size)
	: UIObject(position, size) {
	this->sprite = sprite;
}

UISprite::~UISprite() {

}

void UISprite::onDraw(Pipeline *pipeline) {
	pipeline->draw(getSprite(), getPosition());
}

