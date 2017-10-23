#ifndef GLES3JNI_BIOME_H
#define GLES3JNI_BIOME_H

#include "WeightedList.h"
#include "HexType.h"

class Biome {
public:
	Biome(WeightedList<HexType*> hexTypes);

	HexType* getRandomHexType();

private:
	WeightedList<HexType*> hexTypes;
};

#endif //GLES3JNI_BIOME_H
