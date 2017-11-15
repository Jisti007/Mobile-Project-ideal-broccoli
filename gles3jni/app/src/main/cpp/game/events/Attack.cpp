#include "Attack.h"

Attack::Attack(Unit* attacker, Unit* defender, int damage) {
	this->attacker = attacker;
	this->defender = defender;
	this->damage = damage;
}

Attack::~Attack() {

}

void Attack::beginAnimation() {

}

bool Attack::animate(float deltaTime) {
	return true;
}

void Attack::endAnimation() {

}

bool Attack::execute() {
	defender->modifyHP(-damage);
	return true;
}

bool Attack::cancel() {
	return false;
}
