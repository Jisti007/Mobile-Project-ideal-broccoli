#include "UISprite.h"

UISprite::UISprite(Sprite* sprite, glm::vec2 position)
	: UISprite(sprite, position, sprite->getSize()){

}

UISprite::UISprite(Sprite *sprite, glm::vec2 position, glm::vec2 size)
	: UISprite(sprite, position, size, 1.0f) {

}

UISprite::UISprite(Sprite* sprite, glm::vec2 position, float scale)
	: UISprite(sprite, position, sprite->getSize(), scale){

}

UISprite::UISprite(Sprite* sprite, glm::vec2 position, glm::vec2 size, float scale)
	: UIObject(position, size){
	this->sprite = sprite;
	this->scale = scale;
}

UISprite::~UISprite() {

}

void UISprite::onDraw(Pipeline *pipeline) {
	pipeline->draw(getSprite(), getPosition(), scale);
}

