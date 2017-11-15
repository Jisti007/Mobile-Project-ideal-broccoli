#include "Scenario.h"

Scenario::Scenario(Campaign* campaign) {
	this->campaign = campaign;
	auto game = campaign->getGame();
	auto assets = game->getAssets();

	auto gold = assets->getResource("gold");

	std::vector<glm::vec3> testFaction1Colors = {{1, 0, 0}, {0, 1, 1}};
	std::vector<glm::vec3> testFaction2Colors = {{0, 1, 0}, {1, 0, 1}};
	std::vector<glm::vec3> testFaction3Colors = {{0, 0, 1}, {1, 1, 0}};
	Faction testFaction1(testFaction1Colors);
	Faction testFaction2(testFaction2Colors);
	Faction testFaction3(testFaction3Colors);
	factions.push_back(testFaction1);
	factions.push_back(testFaction2);
	factions.push_back(testFaction3);
	testFaction1.addResource(gold, 100);

	maps.push_back(
		std::make_unique<GameMap>(160, 160, this)
	);
}

Scenario::~Scenario() {

}

void Scenario::executeEvent(std::unique_ptr<ScenarioEvent>& event) {
	event->execute();
	animationQueue.push(std::move(event));
}
