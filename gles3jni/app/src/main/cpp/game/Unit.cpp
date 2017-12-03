#include "Unit.h"
#include "scenes/DeathAnimation.h"
#include "scenes/MovementAnimation.h"

Unit::Unit(uint16_t gridX, uint16_t gridY, UnitType *type, Faction* faction, GameMap* map)
	: MapObject(gridX, gridY) {
	this->type = type;
	this->hp = type->getHP();
	this->faction = faction;
	this->map = map;
}

Unit::~Unit() {

}

bool Unit::move(Path& path) {
	auto destinationHex = static_cast<MapHex*>(path.getLinks().back()->getDestination());
	if (moveTo(destinationHex)) {
		modifyMovement(-path.getCost());

		auto scene = getMap()->getScene();
		for (auto& link : path.getLinks()) {
			auto linkDestinationHex = static_cast<MapHex*>(link->getDestination());
			scene->queueNew<MovementAnimation>(
				getActor(), linkDestinationHex->getActor()->getPosition()
			);
		}
		return true;
	}
	return false;
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
	scene->queueNew<DeathAnimation>(getActor(), scene);
}

void Unit::setHP(int hp) {
	this->hp = hp;
	if (hp <= 0) {
		die();
	}
}

void Unit::onBeginTurn() {
	movable = true;
	movementRemaining = getType()->getMovement();
}

MapHex* Unit::getHex() {
	return map->tryGetHex(getGridPosition());
}

bool Unit::isFriendlyTowards(Unit* other) {
	return getFaction() == other->getFaction();
}
