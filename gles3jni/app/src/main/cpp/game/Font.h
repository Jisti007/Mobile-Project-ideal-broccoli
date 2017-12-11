#ifndef GLES3JNI_FONT_H
#define GLES3JNI_FONT_H

#include <unordered_map>
#include "Sprite.h"

struct Character {
	Sprite* sprite;
	float advance;
};

class Font {
public:
	Font(std::unordered_map<char, Character> mappings, float size);
	inline Character getCharacter(char character){ return mappings[character]; }
	inline const float getSize() const { return size; }

private:
	std::unordered_map<char, Character> mappings;
	float size;
};

#endif //GLES3JNI_FONT_H
