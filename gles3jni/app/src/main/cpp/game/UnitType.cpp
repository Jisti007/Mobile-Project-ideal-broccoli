#include "UnitType.h"
#include "Unit.h"

HPModification::HPModification(int amount) {
	this->amount = amount;
}

void HPModification::apply(MapObject* user, MapObject* target) {
	auto targetUnit = static_cast<Unit*>(target);
	targetUnit->modifyHP(amount);
}

float HPModification::evaluate(MapObject* user, MapObject* target) {
	auto userUnit = static_cast<Unit*>(user);
	auto targetUnit = static_cast<Unit*>(target);
	if (userUnit->isFriendlyTowards(targetUnit)) {
		return amount;
	}
	return -amount;
}

Skill::Skill(
	Sprite* sprite, TargetType targetType, int range, float cost, EffectList& effects
) {
	this->sprite = sprite;
	this->targetType = targetType;
	this->range = range;
	this->cost = cost;
	this->effects = std::move(effects);
}

float Skill::evaluate(MapObject* user, MapObject* target) {
	float evaluation = 0.0f;
	for (auto& effect : effects) {
		evaluation += effect->evaluate(user, target);
	}
	return evaluation;
}

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
