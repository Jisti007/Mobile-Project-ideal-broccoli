#ifndef GLES3JNI_UNIT_H
#define GLES3JNI_UNIT_H

#include "UnitType.h"

class Unit {
public:
    Unit();
    Unit(uint16_t posX, uint16_t posY, UnitType *type);
    ~Unit();

    void initialize(uint16_t posX, uint16_t posY, UnitType *type);

    inline const UnitType* getType() const { return type; }
    inline const uint16_t getX() const { return posX; }
    inline const uint16_t getY() const { return posY; }

private:
    uint16_t posX, posY;
    UnitType* type;
};

#endif //GLES3JNI_UNIT_H
