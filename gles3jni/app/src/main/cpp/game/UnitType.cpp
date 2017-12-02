#include "UnitType.h"
#include "Unit.h"

UnitType::UnitType(
	Sprite* sprite, int hp, int attack, int defense,
	int range, int movement, SkillList& skills
) {
	this->sprite = sprite;
	this->hp = hp;
	this->attack = attack;
	this->defense = defense;
	this->range = range;
	this->movement = movement;
	this->skills = std::move(skills);
}

const std::vector<Skill*> UnitType::getValidSkills(MapObject* user, MapObject* target) const {
	std::vector<Skill*> validSkills;
	for (auto& skill :skills) {
		if (skill->validate(user, target)) {
			validSkills.push_back(skill.get());
		}
	}
	return validSkills;
}
