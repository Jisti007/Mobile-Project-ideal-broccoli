#include "Building.h"
#include "scenes/RecoloredActor.h"

Building::Building(uint16_t gridX, uint16_t gridY, BuildingType *type, Faction* faction)
	: MapObject(gridX, gridY) {
	this->type = type;
	this->faction = faction;
}

Building::~Building() {}

void Building::onBeginTurn(GameMap* map) {
	auto activeFaction = map->getScenario()->getActiveFaction();
	if (faction == activeFaction) {
		for(auto& resourceProduction : getType()->getResourceProductions()) {
			faction->modifyResource(resourceProduction);
		}
	}
}

void Building::setFaction(Faction* faction) {
	this->faction = faction;
	auto actor = static_cast<RecoloredActor*>(getActor());
	// TODO: Queue an Animation to change the color instead.
	actor->setColors(faction->getColors());
}
