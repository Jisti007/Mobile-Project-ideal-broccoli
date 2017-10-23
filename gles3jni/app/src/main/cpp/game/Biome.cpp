#include "Biome.h"

Biome::Biome(WeightedList<HexType*> hexTypes) {
	this->hexTypes = hexTypes;
}

HexType* Biome::getRandomHexType() {
	return hexTypes.getRandom();
}
