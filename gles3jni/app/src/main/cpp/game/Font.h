//
// Created by K1697 on 8.11.2017.
//

#ifndef GLES3JNI_FONT_H
#define GLES3JNI_FONT_H


#include <unordered_map>
#include "Sprite.h"

class Font {
public:
	Font(std::unordered_map<char, Sprite*> mapping);
	inline Sprite* getSprite(char character){ return mapping[character]; }

private:
	std::unordered_map<char, Sprite*> mapping;
};


#endif //GLES3JNI_FONT_H
