#include "Font.h"

Font::Font(std::unordered_map<char, Sprite*> mapping) {
	this->mappings = mapping;
}
