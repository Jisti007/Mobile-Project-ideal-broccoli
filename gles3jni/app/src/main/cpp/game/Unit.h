#ifndef GLES3JNI_UNIT_H
#define GLES3JNI_UNIT_H

#include "UnitType.h"
#include "MapObject.h"

class Unit : public MapObject {
public:
    Unit();
    Unit(uint16_t gridX, uint16_t gridY, UnitType *type);
    ~Unit();

    inline const UnitType* getType() const { return type; }

	virtual Sprite* getSprite() {return type->getSprite(); }

private:
    UnitType* type;
};

#endif //GLES3JNI_UNIT_H
