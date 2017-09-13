#ifndef GLES3JNI_RULESET_H
#define GLES3JNI_RULESET_H

#include <unordered_map>
#include "HexType.h"
#include "UnitType.h"
#include "Resource.h"
#include "BuildingType.h"

class Ruleset {
private:
    std::unordered_map<char*, HexType> hexTypes;
    std::unordered_map<char*, UnitType> unitTypes;
    std::unordered_map<char*, BuildingType> buildingTypes;
    std::unordered_map<char*, Resource> resources;
};

#endif //GLES3JNI_RULESET_H
