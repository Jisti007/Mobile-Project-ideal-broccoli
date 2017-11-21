#ifndef GLES3JNI_MAPOBJECT_H
#define GLES3JNI_MAPOBJECT_H

#include <cstdint>
#include "Sprite.h"
#include "Point.h"
#include "scenes/Actor.h"

class MapObject {
public:
	MapObject(uint16_t gridX, uint16_t gridY);
	virtual ~MapObject();

	virtual Sprite* getSprite() = 0;

	inline Actor* getActor() { return actor; }
	inline void setActor(Actor* actor) { this->actor = actor; }
	inline const uint16_t getGridX() const { return gridX; }
	inline const uint16_t getGridY() const { return gridY; }
	inline Point getGridPosition() { return Point{getGridX(), getGridY()}; }

protected:
	uint16_t gridX, gridY;

private:
	Actor* actor = nullptr;
};

#endif //GLES3JNI_MAPOBJECT_H
