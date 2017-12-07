#include "UnitType.h"
#include "Unit.h"

UnitType::UnitType(
	Sprite* sprite, std::string name, int hp, int defense, int movement, SkillList& skills
) {
	this->sprite = sprite;
	this->name = name;
	this->hp = hp;
	this->defense = defense;
	this->movement = movement;
	this->skills = std::move(skills);
}

const std::vector<Skill*> UnitType::getValidSkills(MapObject* user, MapObject* target) const {
	std::vector<Skill*> validSkills;
	for (auto& skill : skills) {
		if (skill->validate(user, target, 0, user->getDistance(target))) {
			validSkills.push_back(skill.get());
		}
	}
	return validSkills;
}

int UnitType::getMaxSkillRange() const {
	int max = 0;
	for (auto& skill : skills) {
		auto range = skill->getRange();
		if (range > max) {
			max = range;
		}
	}
	return max;
}
