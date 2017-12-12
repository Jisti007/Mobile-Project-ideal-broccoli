#include "Scenario.h"
#include "states/MapGameState.h"
#include "states/PlayerGameState.h"
#include "states/ComputerGameState.h"
#include "states/IdleGameState.h"

Scenario::Scenario(Campaign* campaign) {
	this->campaign = campaign;
	auto game = campaign->getGame();
	auto assets = game->getAssets();

	//TODO: Make a system for displaying all non-hardcoded resources the active player possesses.
	auto gold = assets->getResource("gold");
	auto food = assets->getResource("food");
	auto material = assets->getResource("material");
	auto crystal = assets->getResource("crystal");

	std::vector<glm::vec3> testFaction1Colors = {{1, 0, 0}, {0, 1, 1}};
	std::vector<glm::vec3> testFaction2Colors = {{0, 1, 0}, {1, 0, 1}};
	std::vector<glm::vec3> testFaction3Colors = {{0, 0, 1}, {1, 1, 0}};
	std::vector<glm::vec3> testFaction4Colors = {{0, 1, 1}, {1, 1, 1}};
	Faction testFaction1(testFaction1Colors);
	Faction testFaction2(testFaction2Colors);
	Faction testFaction3(testFaction3Colors);
	Faction testFaction4(testFaction4Colors);
	testFaction1.setPlayer(true);

	//TODO: RESOURCES FOR DEMO, maybe fix afterwards
	testFaction1.modifyResource(gold, 1500);
	testFaction1.modifyResource(food, 1000);
	testFaction1.modifyResource(material, 250);
	testFaction1.modifyResource(crystal, 50);

	testFaction2.modifyResource(gold, 1500);
	testFaction2.modifyResource(food, 1000);
	testFaction2.modifyResource(material, 250);
	testFaction2.modifyResource(crystal, 50);

	testFaction3.modifyResource(gold, 1500);
	testFaction3.modifyResource(food, 1000);
	testFaction3.modifyResource(material, 250);
	testFaction3.modifyResource(crystal, 50);

	testFaction4.modifyResource(gold, 1500);
	testFaction4.modifyResource(food, 1000);
	testFaction4.modifyResource(material, 250);
	testFaction4.modifyResource(crystal, 50);

	factions.push_back(testFaction1);
	factions.push_back(testFaction2);
	factions.push_back(testFaction3);
	factions.push_back(testFaction4);

	maps.push_back(
		std::make_unique<GameMap>(64, 64, this)
	);

	for (auto& map : maps) {
		map->onBeginTurn();
	}
}

Scenario::~Scenario() {

}

void Scenario::executeEvent(std::unique_ptr<ScenarioEvent>& event) {
	if (event->execute()) {
		animationQueue.push(event.get());
		eventLog.push_back(std::move(event));
	}
}

void Scenario::endTurn() {
	activeFactionIndex++;
	if (activeFactionIndex >= getFactionCount()) {
		turn++;
		activeFactionIndex = 0;
	}

	for (auto& map : maps) {
		map->onBeginTurn();
	}

	auto game = getCampaign()->getGame();
	//std::unique_ptr<GameState> unitSelectedState(new PlayerGameState(game));
	//game->changeState(unitSelectedState);
	if (getActiveFaction()->isPlayer()) {
		game->changeToNew<IdleGameState>(game);
	} else {
		game->changeToNew<ComputerGameState>(game);
	}
}
