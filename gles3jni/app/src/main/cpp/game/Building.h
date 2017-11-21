#ifndef GLES3JNI_BUILDING_H
#define GLES3JNI_BUILDING_H

#include "BuildingType.h"
#include "MapObject.h"
#include "Faction.h"

class Building : public MapObject {
public:
	Building(uint16_t gridX, uint16_t gridY, BuildingType *type, Faction* faction);
	virtual ~Building();

	virtual Sprite* getSprite() {return type->getSprite(); }

	inline const BuildingType* getType() const { return type; }
	inline const Faction* getFaction() const { return faction; }

private:
	BuildingType* type;
	Faction* faction;
};

#endif //GLES3JNI_BUILDING_H
