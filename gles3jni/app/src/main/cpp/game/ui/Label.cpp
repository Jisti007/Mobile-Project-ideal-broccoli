#include "Label.h"

Label::Label(const char* text, Font* font, glm::vec2 position, glm::vec2 size) : UIObject(position, size) {
	this->text = text;
	this->font = font;

}

void Label::onDraw(Pipeline* pipeline) {
	size_t i = 0;
	//int maxRowHeight = 0;
	glm::vec2 offset = getPosition();

	while(text[i] != '\0') {
		char c = text[i];

		Sprite* sprite = font->getCharacter(c).sprite;
		pipeline->draw(sprite, offset);
		offset.x += sprite->getWidth()+5;
		i++;
	}


	UIObject::onDraw(pipeline);
}

