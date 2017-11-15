#include "Scenario.h"

Scenario::Scenario(Campaign* campaign) {
	this->campaign = campaign;
	auto game = campaign->getGame();
	auto assets = game->getAssets();

	auto gold = assets->getResource("gold");
	auto food = assets->getResource("food");
	auto material = assets->getResource("material");
	auto crystal = assets->getResource("crystal");

	std::vector<glm::vec3> testFaction1Colors = {{1, 0, 0}, {0, 1, 1}};
	std::vector<glm::vec3> testFaction2Colors = {{0, 1, 0}, {1, 0, 1}};
	std::vector<glm::vec3> testFaction3Colors = {{0, 0, 1}, {1, 1, 0}};
	Faction testFaction1(testFaction1Colors);
	Faction testFaction2(testFaction2Colors);
	Faction testFaction3(testFaction3Colors);
	testFaction1.modifyResource(gold, 150);
	testFaction1.modifyResource(food, 100);
	testFaction1.modifyResource(material, 25);
	testFaction1.modifyResource(crystal, 5);
	factions.push_back(testFaction1);
	factions.push_back(testFaction2);
	factions.push_back(testFaction3);

	maps.push_back(
		std::make_unique<GameMap>(160, 160, this)
	);
}

Scenario::~Scenario() {

}

void Scenario::executeEvent(std::unique_ptr<ScenarioEvent>& event) {
	event->execute();
	animationQueue.push(event.get());
	eventLog.push_back(std::move(event));
}

void Scenario::endTurn() {
	activeFactionIndex++;
	if (activeFactionIndex <= getFactionCount()) {
		turn++;
		activeFactionIndex = 0;
	}
}
