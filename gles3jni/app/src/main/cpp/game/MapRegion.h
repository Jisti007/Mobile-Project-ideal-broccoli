#ifndef GLES3JNI_MAPREGION_H
#define GLES3JNI_MAPREGION_H

class MapHex;

#include <vector>
#include "MapHex.h"
#include "Biome.h"

class MapRegion {
public:
	MapRegion();
	MapRegion(Biome* biome);

	void expandTo(MapHex* hex);
	bool expandRandom();

	inline Biome* getBiome() { return biome; }

private:
	std::vector<MapHex*> borderHexes;
	Biome* biome;

	void expand(int borderHexIndex);
};

#endif //GLES3JNI_MAPREGION_H
