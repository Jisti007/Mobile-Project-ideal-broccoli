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

bool Unit::move(Path path) {
	auto& links = path.getLinks();
	while (true) {
		if (links.size() == 0) {
			return true;
		}
		auto lastLink = links.back();
		auto lastHex = static_cast<MapHex*>(lastLink->getDestination());
		if (path.getCost() > getMovement() || !canMoveTo(lastHex)) {
			path.popLast();
		} else {
			break;
		}
	}

	auto destinationHex = static_cast<MapHex*>(links.back()->getDestination());
	if (moveTo(destinationHex)) {
		modifyMovement(-path.getCost());

		auto scene = getMap()->getScene();
		for (auto& link : links) {
			auto linkDestinationHex = static_cast<MapHex*>(link->getDestination());
			scene->queueNew<MovementAnimation>(
				getActor(), scene, linkDestinationHex->getActor()->getPosition(), true
			);
		}
		return true;
	}

	return false;
}

bool Unit::moveTo(MapHex* destination) {
	if (!canMoveTo(destination)) {
		return false;
	}

	auto origin = map->tryGetHex(getGridX(), getGridY());
	if (origin->getUnit() == this) {
		origin->setUnit(nullptr);
	}

	destination->setUnit(this);
	gridX = destination->getGridX();
	gridY = destination->getGridY();

	auto building = destination->getBuilding();
	if (building) {
		if (getFaction() != building->getFaction()) {
			building->setFaction(getFaction());
		}
	}

	return true;
}

bool Unit::canMoveTo(MapHex* destination) {
	if (destination->getUnit() != nullptr) {
		return false;
	}

	MapHex* origin = map->tryGetHex(getGridX(), getGridY());
	return origin != nullptr;
}

void Unit::die() {
	map->removeUnit(this);
	auto scene = map->getScene();
	scene->queueNew<DeathAnimation>(getActor(), scene, 1.0f);
}

void Unit::setHP(int hp) {
	auto maxHP = type->getHP();
	if (hp > maxHP) {
		hp = maxHP;
	} else if (hp <= 0) {
		die();
	}
	this->hp = hp;
}

void Unit::onBeginTurn() {
	//movable = true;
	movementRemaining = getType()->getMovement();

	auto activeFaction = getMap()->getScenario()->getActiveFaction();
	if (getFaction() == activeFaction) {
		if (!getFaction()->hasResources(getType()->getUpkeep())) {
			die();
		} else {
			for (auto& upkeepResourceAmount : getType()->getUpkeep()) {
				getFaction()->subtractResource(upkeepResourceAmount);
			}
		}
	}
}

MapHex* Unit::getHex() {
	return map->tryGetHex(getGridPosition());
}

bool Unit::isFriendlyTowards(Unit* other) {
	return getFaction() == other->getFaction();
}

int Unit::getDamageModifierAgainst(Damage* damage) {
	return type->getDamageModifierAgainst(damage);
}
