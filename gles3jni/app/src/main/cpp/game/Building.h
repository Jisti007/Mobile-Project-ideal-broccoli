#ifndef GLES3JNI_BUILDING_H
#define GLES3JNI_BUILDING_H

#include "BuildingType.h"

class Building {
public:
	Building();
	Building(uint16_t posX, uint16_t posY, BuildingType *type);
	~Building();

	void initialize(uint16_t posX, uint16_t posY, BuildingType *type);

	inline const BuildingType* getType() const { return type; }
	inline const uint16_t getX() const { return posX; }
	inline const uint16_t getY() const { return posY; }

private:
	uint16_t posX, posY;
	BuildingType* type;
};

#endif //GLES3JNI_BUILDING_H
