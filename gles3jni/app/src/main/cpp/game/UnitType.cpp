#include "UnitType.h"

UnitType::UnitType(Sprite *sprite, int hp, int attack, int defense, int range, int movement) {
	this->sprite = sprite;
	this->hp = hp;
	this->attack = attack;
	this->defense = defense;
	this->range = range;
	this->movement = movement;
}

UnitType::~UnitType() {

}
