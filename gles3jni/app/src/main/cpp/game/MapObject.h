//
// Created by K1697 on 12.10.2017.
//

#ifndef GLES3JNI_MAPOBJECT_H
#define GLES3JNI_MAPOBJECT_H

#include <cstdint>
#include "Sprite.h"

class MapObject {
public:
	MapObject(uint16_t gridX, uint16_t gridY);
	virtual ~MapObject();

	inline const uint16_t getGridX() const { return gridX; }
	inline const uint16_t getGridY() const { return gridY; }

	virtual Sprite* getSprite() = 0;

protected:
	uint16_t gridX, gridY;
};

#endif //GLES3JNI_MAPOBJECT_H
