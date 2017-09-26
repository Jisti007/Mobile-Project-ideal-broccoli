#ifndef GLES3JNI_MAPHEX_H
#define GLES3JNI_MAPHEX_H
#include "HexType.h"

class MapHex {
public:
	MapHex();
    MapHex(uint16_t gridX, uint16_t gridY, HexType* type);
	~MapHex();

	void initialize(uint16_t gridX, uint16_t gridY, HexType* type);

private:
	uint16_t gridX, gridY;
    HexType* type;
};

#endif //GLES3JNI_MAPHEX_H
