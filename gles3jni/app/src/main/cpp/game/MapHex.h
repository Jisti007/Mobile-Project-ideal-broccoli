#ifndef GLES3JNI_MAPHEX_H
#define GLES3JNI_MAPHEX_H

#include "HexType.h"
#include "Unit.h"

class MapHex : public MapObject {
public:
	MapHex();
	MapHex(uint16_t gridX, uint16_t gridY, HexType *type);
	~MapHex();

	void initialize(uint16_t gridX, uint16_t gridY, HexType* type);

	inline const HexType* getType() const { return type; }
	virtual Sprite* getSprite() {return type->getSprite(); }
private:
	HexType *type;
	Unit* unit;
};

#endif //GLES3JNI_MAPHEX_H
