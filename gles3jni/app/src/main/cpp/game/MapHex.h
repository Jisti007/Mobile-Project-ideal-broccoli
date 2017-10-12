#ifndef GLES3JNI_MAPHEX_H
#define GLES3JNI_MAPHEX_H

#include "HexType.h"
#include "Unit.h"

class MapHex {
public:
	MapHex();
	MapHex(uint16_t gridX, uint16_t gridY, HexType *type);
	~MapHex();

	void initialize(uint16_t gridX, uint16_t gridY, HexType *type);

	inline const HexType* getType() const { return type; }
	inline const uint16_t getGridX() const { return gridX; }
	inline const uint16_t getGridY() const { return gridY; }

private:
	uint16_t gridX, gridY;
	HexType *type;
	Unit* unit;
};

#endif //GLES3JNI_MAPHEX_H
