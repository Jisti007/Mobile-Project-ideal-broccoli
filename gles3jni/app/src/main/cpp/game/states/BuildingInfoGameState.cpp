#include "BuildingInfoGameState.h"

BuildingInfoGameState::BuildingInfoGameState(Game* game, Building* selectedBuilding) : PlayerGameState(game) {
	this->selectedBuilding = selectedBuilding;
	createUI();
}

void BuildingInfoGameState::recreateUI() {
	PlayerGameState::recreateUI();
	createUI();
}

void BuildingInfoGameState::createUI() {
	auto assets = game->getAssets();
	//auto viewport = game->getPipeline()->getViewport();

	auto infoPanelSprite = assets->getSprite("ui_info");
	auto infoPanel = uiRoot->addNewChild<InfoPanel>(
		infoPanelSprite, glm::vec2{
			0,0},
	    assets->getFont("default"),
	    assets,
	    game
	);

	auto map = game->getCampaign()->getScenario()->getActiveMap();

	if (selectedBuilding->getType()->getRecruitments().empty()) {
		infoPanel->updateInfo(selectedBuilding);
	} else {
		auto testPanelSprite = assets->getSprite("faction_crest");
		auto testPanel = uiRoot->addNewChild<InfoPanel>(
			testPanelSprite, glm::vec2{
				0,0},
			assets->getFont("default"),
			assets,
			game
		);
	}
}

void BuildingInfoGameState::move(float dx, float dy) {
	game->popState();
}

bool BuildingInfoGameState::press(float x, float y) {
	if(GameState::press(x, y)) {
		return true;
	}
	game->popState();
	return true;
}

void BuildingInfoGameState::zoom(float scaleFactor) {
	game->popState();
}
