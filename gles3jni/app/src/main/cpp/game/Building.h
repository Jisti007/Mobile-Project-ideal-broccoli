#ifndef GLES3JNI_BUILDING_H
#define GLES3JNI_BUILDING_H

#include "BuildingType.h"

class Building {
public:
	Building();
	Building(uint16_t gridX, uint16_t gridY, BuildingType *type);
	~Building();

	void initialize(uint16_t gridX, uint16_t gridY, BuildingType *type);

	inline const BuildingType* getType() const { return type; }
	inline const uint16_t getGridX() const { return gridX; }
	inline const uint16_t getGridY() const { return gridY; }

private:
	uint16_t gridX, gridY;
	BuildingType* type;
};

#endif //GLES3JNI_BUILDING_H
