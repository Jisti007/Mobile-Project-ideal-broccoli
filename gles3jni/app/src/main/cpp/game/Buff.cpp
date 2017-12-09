#include "Buff.h"

Resistance::Resistance(DamageType* type, int amount) {

}

int Resistance::getDamageModifierAgainst(Damage* damage) {
	if (damage->getType() == type) {
		return -amount;
	}
	return 0;
}

Buff::Buff(Buff::EffectList& effects, const char* name, Sprite* sprite) {
	this->effects = std::move(effects);
	this->name = name;
	this->sprite = sprite;
}

int Buff::getDamageModifierAgainst(Damage* damage) {
	int modifier = 0;
	for (auto& effect : effects) {
		modifier += effect->getDamageModifierAgainst(damage);
	}
	return modifier;
}

