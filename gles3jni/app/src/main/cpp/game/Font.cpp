#include "Font.h"

Font::Font(std::unordered_map<char, Character> mappings, float size) {
	this->mappings = mappings;
	this->size = size;
}
