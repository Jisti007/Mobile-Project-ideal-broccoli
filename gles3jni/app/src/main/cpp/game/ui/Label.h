#ifndef GLES3JNI_LABEL_H
#define GLES3JNI_LABEL_H

#include "UISprite.h"
#include "../Font.h"

class Label : public UIObject {

public:
	Label(const char* text, Font* font, glm::vec2 position, glm::vec2 size);
	void setText(const char* text) {this->text = text;}
	virtual void onDraw(Pipeline* pipeline);

private:
	Font* font;
	std::string text;
};

#endif //GLES3JNI_LABEL_H
