#ifndef GLES3JNI_UNIT_H
#define GLES3JNI_UNIT_H

#include "UnitType.h"

class Unit {
public:
    Unit();
    Unit(uint16_t gridX, uint16_t gridY, UnitType *type);
    ~Unit();

    void initialize(uint16_t gridX, uint16_t gridY, UnitType *type);

    inline const UnitType* getType() const { return type; }
    inline const uint16_t getGridX() const { return gridX; }
    inline const uint16_t getGridY() const { return gridY; }

private:
    uint16_t gridX, gridY;
    UnitType* type;
};

#endif //GLES3JNI_UNIT_H
