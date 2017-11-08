#ifndef GLES3JNI_MAPOBJECT_H
#define GLES3JNI_MAPOBJECT_H

#include <cstdint>
#include "Sprite.h"
#include "Point.h"

class MapObject {
public:
	MapObject(uint16_t gridX, uint16_t gridY);
	virtual ~MapObject();

	inline const uint16_t getGridX() const { return gridX; }
	inline const uint16_t getGridY() const { return gridY; }
	inline Point getGridPosition() { return Point{getGridX(), getGridY()}; }
	inline glm::vec2 getPosition() { return position; }
	inline void setPosition(glm::vec2 position) { this->position = position; }

	virtual Sprite* getSprite() = 0;

protected:
	uint16_t gridX, gridY;
	glm::vec2 position;
};

#endif //GLES3JNI_MAPOBJECT_H
