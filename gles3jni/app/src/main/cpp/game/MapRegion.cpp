#include "MapRegion.h"

MapRegion::MapRegion() {

}

MapRegion::MapRegion(Biome* biome) {
	this->biome = biome;
}

void MapRegion::expandTo(MapHex* hex) {
	if (hex && !hex->getRegion()) {
		borderHexes.push_back(hex);
		hex->setRegion(this);
	}
}

bool MapRegion::expandRandom() {
	if (borderHexes.size() == 0) {
		return false;
	}

	expand(rand() % (int)borderHexes.size());
	return true;
}

void MapRegion::expand(int borderHexIndex) {
	auto hex = borderHexes[borderHexIndex];

	for (auto neighbor : hex->getNeighbors()) {
		expandTo(neighbor);
	}

	borderHexes.erase(borderHexes.begin() + borderHexIndex);
}
