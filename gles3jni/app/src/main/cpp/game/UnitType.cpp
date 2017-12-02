#include "UnitType.h"
#include "Unit.h"

HPModification::HPModification(int amount) {
	this->amount = amount;
}

void HPModification::apply(MapObject* target) {
	auto targetUnit = static_cast<Unit*>(target);
	targetUnit->modifyHP(amount);
}

Skill::Skill(Sprite* sprite, Target target, int range, float cost, std::vector<Effect*> effects) {
	this->sprite = sprite;
	this->target = target;
	this->range = range;
	this->cost = cost;
	this->effects = effects;
}

UnitType::UnitType(Sprite *sprite, int hp, int attack, int defense, int range, int movement) {
	this->sprite = sprite;
	this->hp = hp;
	this->attack = attack;
	this->defense = defense;
	this->range = range;
	this->movement = movement;
}
