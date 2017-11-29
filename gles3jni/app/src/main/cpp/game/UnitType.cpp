#include "UnitType.h"

UnitType::UnitType(Sprite *sprite, int hp, int attack, int defense, int range) {
	this->sprite = sprite;
	this->hp = hp;
	this->attack = attack;
	this->defense = defense;
	this->range = range;
}

UnitType::~UnitType() {

}
