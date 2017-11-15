#include "Campaign.h"

Campaign::Campaign(Game* game) {
	this->game = game;
	scenario = std::make_unique<Scenario>(this);
}

Campaign::~Campaign() {

}
