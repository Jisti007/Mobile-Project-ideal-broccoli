#ifndef GLES3JNI_UNIT_H
#define GLES3JNI_UNIT_H

#include "UnitType.h"
#include "MapObject.h"
#include "Faction.h"

class Unit : public MapObject {
public:
	Unit();
	Unit(uint16_t gridX, uint16_t gridY, UnitType *type, Faction* faction);
	virtual ~Unit();

	virtual Sprite* getSprite() {return type->getSprite(); }

	inline const UnitType* getType() const { return type; }
	inline const Faction* getFaction() const { return faction; }

private:
    UnitType* type;
	Faction* faction;
};

#endif //GLES3JNI_UNIT_H
