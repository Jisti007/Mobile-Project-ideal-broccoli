#include "Label.h"

Label::Label(const char* text, Font* font, glm::vec2 position, glm::vec2 size) : UIObject(position, size) {
	this->text = text;
	this->font = font;

}

void Label::onDraw(Pipeline* pipeline) {
	size_t i = 0;
	//int maxRowHeight = 0;
	glm::vec2 offset = getPosition();
	auto originalPosition = offset;

	while(text[i] != '\0') {
		if (text[i] == '\n') {
			offset.x = originalPosition.x;
			offset.y -= font->getSize();
			i++;
		} else {
			char c = text[i];
			auto character = font->getCharacter(c);
			offset.x += character.advance;
			if (offset.x > this->getSize().x){
				offset.x = originalPosition.x;
				offset.y -= font->getSize();
			}
			Sprite* sprite = character.sprite;
			pipeline->draw(sprite, offset);
			i++;
		}
	}

	UIObject::onDraw(pipeline);
}

