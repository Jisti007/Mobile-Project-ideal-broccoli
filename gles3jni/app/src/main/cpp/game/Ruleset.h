#ifndef GLES3JNI_RULESET_H
#define GLES3JNI_RULESET_H

#include <unordered_map>
#include "HexType.h"
#include "UnitType.h"
#include "Resource.h"
#include "BuildingType.h"

class Ruleset {
public:
    Ruleset(const char* xmlPath);
    ~Ruleset();

private:
	std::unordered_map<const char*, Texture> textures;
    std::unordered_map<const char*, HexType> hexTypes;
    std::unordered_map<const char*, UnitType> unitTypes;
    std::unordered_map<const char*, BuildingType> buildingTypes;
    std::unordered_map<const char*, Resource> resources;

	void loadAssets(const char* xmlPath);
};

#endif //GLES3JNI_RULESET_H
