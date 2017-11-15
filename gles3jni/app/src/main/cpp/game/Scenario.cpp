#include "Scenario.h"

Scenario::Scenario(Campaign* campaign) {
	this->campaign = campaign;
	auto game = campaign->getGame();
	//auto map = std::make_unique<GameMap>(160, 160, game->getAssets(), game->getPipeline());
	maps.push_back(
		std::make_unique<GameMap>(160, 160, game->getAssets(), game->getPipeline())
	);
}

Scenario::~Scenario() {

}

void Scenario::executeEvent(std::unique_ptr<ScenarioEvent>& event) {
	event->execute();
	animationQueue.push(std::move(event));
}
