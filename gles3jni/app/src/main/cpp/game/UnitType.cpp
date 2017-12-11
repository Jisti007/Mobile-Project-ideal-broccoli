#include "UnitType.h"
#include "Unit.h"

UnitType::UnitType(
	Sprite* sprite, std::string name, int hp, int defense, int movement,
	SkillList& skills, BuffList& buffs, ResourceAmountList upkeep
) {
	this->sprite = sprite;
	this->name = name;
	this->hp = hp;
	this->defense = defense;
	this->movement = movement;
	this->skills = std::move(skills);
	this->buffs = std::move(buffs);
	this->upkeep = upkeep;
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

int UnitType::getDamageModifierAgainst(Damage* damage) {
	int modifier = 0;
	for (auto& buff : buffs) {
		modifier += buff->getDamageModifierAgainst(damage);
	}
	return modifier;
}
