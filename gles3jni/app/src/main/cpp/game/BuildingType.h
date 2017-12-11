#ifndef GLES3JNI_BUILDINGTYPE_H
#define GLES3JNI_BUILDINGTYPE_H

#include "Sprite.h"
#include "Resource.h"
#include "UnitType.h"

class Recruitment {

public:
	Recruitment(UnitType* unitType, int time, std::vector<ResourceAmount> resourceCosts);

private:
	UnitType* unitType;
	int time;
	std::vector<ResourceAmount> resourceCosts;
};

class BuildingType {
public:
	BuildingType(
		Sprite* sprite, std::string name, std::string description,
		std::vector<ResourceAmount> resourceProductions, std::vector<Recruitment> recruitments);
	~BuildingType();

	inline Sprite* getSprite() const { return sprite; }
	inline const std::vector<ResourceAmount> getResourceProductions() const { return resourceProductions; }
	inline const std::string getName() const { return name; };
	inline const std::string getDescription() const { return description; };
	inline const std::vector<Recruitment> getRecruitments() const { return recruitments; };

private:
	Sprite* sprite;
	std::string name, description;
	std::vector<ResourceAmount> resourceProductions;
	std::vector<Recruitment> recruitments;
};

#endif //GLES3JNI_BUILDINGTYPE_H
