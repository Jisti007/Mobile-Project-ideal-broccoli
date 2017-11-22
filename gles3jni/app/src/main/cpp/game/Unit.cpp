#include "Unit.h"
#include "scenes/DeathAnimation.h"

Unit::Unit(uint16_t gridX, uint16_t gridY, UnitType *type, Faction* faction, GameMap* map)
	: MapObject(gridX, gridY) {
	this->type = type;
	this->hp = type->getHP();
	this->faction = faction;
	this->map = map;
}

Unit::~Unit() {

}

bool Unit::moveTo(MapHex* destination) {
	if (destination->getUnit() != nullptr) {
		return false;
	}

	MapHex* origin = map->tryGetHex(getGridX(), getGridY());
	if (origin == nullptr) {
		return false;
	}

	if (origin->getUnit() == this) {
		origin->setUnit(nullptr);
	}

	destination->setUnit(this);
	gridX = destination->getGridX();
	gridY = destination->getGridY();

	return true;
}

void Unit::die() {
	map->removeUnit(this);
	auto scene = map->getScene();
	std::unique_ptr<Animation> animation(new DeathAnimation(getActor(), scene));
	scene->queueAnimation(animation);
}

void Unit::setHP(int hp) {
	this->hp = hp;
	if (hp < 0) {
		die();
	}
}
