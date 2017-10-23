#include "MapRegion.h"

MapRegion::MapRegion(Biome* biome) {
	this->biome = biome;
}

void MapRegion::expandTo(MapHex* hex) {
	if (hex && !hex->getRegion()) {
		borderHexes.push_back(hex);
		hex->setRegion(this);
	}
}

void MapRegion::expand(int borderHexIndex) {
	auto hex = borderHexes[borderHexIndex];
	borderHexes.erase(borderHexes.begin() + borderHexIndex);

	for (auto& neighbor : hex->getNeighbors()) {
		expandTo(neighbor);
	}
}

bool MapRegion::expandRandom() {
	if (borderHexes.size() == 0) {
		return false;
	}

	expand(rand() % (int)borderHexes.size());
	return true;
}
