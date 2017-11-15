#include "Button.h"

Button::Button(Sprite* sprite, glm::vec2 position)
	: UISprite(sprite, position) {

}

Button::Button(Sprite *sprite, glm::vec2 position, glm::vec2 size)
	: UISprite(sprite, position, size) {

}
