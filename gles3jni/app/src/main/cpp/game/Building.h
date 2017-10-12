#ifndef GLES3JNI_BUILDING_H
#define GLES3JNI_BUILDING_H

#include "BuildingType.h"
#include "MapObject.h"

class Building : public MapObject {
public:
	Building();
	Building(uint16_t gridX, uint16_t gridY, BuildingType *type);
	~Building();

	inline const BuildingType* getType() const { return type; }
	virtual Sprite* getSprite() {return type->getSprite(); }
private:
	BuildingType* type;
};

#endif //GLES3JNI_BUILDING_H
