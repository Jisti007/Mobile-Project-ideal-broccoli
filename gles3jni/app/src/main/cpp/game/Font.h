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
	Font(std::unordered_map<char, Character> mappings);
	inline Character getCharacter(char character){ return mappings[character]; }

private:
	std::unordered_map<char, Character> mappings;
};

#endif //GLES3JNI_FONT_H
