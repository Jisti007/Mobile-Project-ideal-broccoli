#ifndef GLES3JNI_MAPHEX_H
#define GLES3JNI_MAPHEX_H

#include "HexType.h"

class MapHex {
public:
	MapHex();
	MapHex(uint16_t gridX, uint16_t gridY, HexType *type);
	~MapHex();

	void initialize(uint16_t gridX, uint16_t gridY, HexType *type);

	inline const uint16_t getGridX() const { return gridX; }
	inline const uint16_t getGridY() const { return gridY; }
	inline const HexType* getType() const { return type; }

private:
	uint16_t gridX, gridY;
	HexType *type;
};

#endif //GLES3JNI_MAPHEX_H
