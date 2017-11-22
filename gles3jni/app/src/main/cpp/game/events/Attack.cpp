#include "Attack.h"

Attack::Attack(Unit* attacker, Unit* defender, int damage) {
	this->attacker = attacker;
	this->defender = defender;
	this->damage = damage;
}

Attack::~Attack() {

}

bool Attack::execute() {
	defender->modifyHP(-damage);
	return true;
}

bool Attack::cancel() {
	// Can't be cancelled, at least for now.
	return false;
}
