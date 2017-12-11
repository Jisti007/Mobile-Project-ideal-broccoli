#include "Font.h"

Font::Font(std::unordered_map<char, Character> mappings) {
	this->mappings = mappings;
}
