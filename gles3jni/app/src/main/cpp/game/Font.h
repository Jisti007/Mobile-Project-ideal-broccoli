#ifndef GLES3JNI_FONT_H
#define GLES3JNI_FONT_H

#include <unordered_map>
#include "Sprite.h"

class Font {
public:
	Font(std::unordered_map<char, Sprite*> mapping);
	inline Sprite* getSprite(char character){ return mappings[character]; }

private:
	std::unordered_map<char, Sprite*> mappings;
};

#endif //GLES3JNI_FONT_H
