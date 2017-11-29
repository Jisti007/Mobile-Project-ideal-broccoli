//
// Created by K1697 on 29.11.2017.
//

#include "PlayerGameState.h"
#include "UnitSelectedGameState.h"
#include "../ui/RecoloredUISprite.h"
#include "../ui/Button.h"

PlayerGameState::PlayerGameState(Game* game) : MapGameState(game) {
	createUI();
}

PlayerGameState::~PlayerGameState() {

}

void PlayerGameState::recreateUI() {
	GameState::recreateUI();
	createUI();
}

void PlayerGameState::update(float deltaTime) {
	// TODO: Move to when resources update
	auto scenario = game->getCampaign()->getScenario();
	//resourcePanel->updateResources(scenario);
}

void PlayerGameState::onPressHex(MapHex* hex) {
	auto scenario = game->getCampaign()->getScenario();
	auto activeFaction = scenario->getActiveFaction();
	auto unit = hex->getUnit();
	if (unit != nullptr && unit->getFaction() == activeFaction) {
		std::unique_ptr<GameState> unitSelectedState(new UnitSelectedGameState(game, unit));
		game->changeState(unitSelectedState);
	}
}

void PlayerGameState::createUI() {

	auto assets = game->getAssets();
	auto scenario = game->getCampaign()->getScenario();
	auto map = scenario->getActiveMap();
	auto viewport = game->getPipeline()->getViewport();

	auto resourcePanelSprite = assets->getSprite("ui_resource");
	resourcePanel = new ResourcePanel(
		resourcePanelSprite, glm::vec2{
			0, viewport.getTop() - resourcePanelSprite->getHeight() / 2.0f
		},
		assets->getFont("default")
	);
	std::unique_ptr<UIObject> resourcePanelPointer(resourcePanel);
	uiRoot->addChild(resourcePanelPointer);

	auto crestSprite = assets->getSprite("faction_crest");
	auto colors = scenario->getActiveFaction()->getColors();
	std::unique_ptr<UIObject> crest(new RecoloredUISprite(
		crestSprite, glm::vec2{
			0 - resourcePanelSprite->getWidth() / 2.0f - crestSprite->getWidth() / 2.0f,
			viewport.getTop() - crestSprite->getHeight() * 0.5f / 2.0f},
		0.5f, colors
	));
	uiRoot->addChild(crest);

	resourcePanel->updateResources(scenario);

	auto endTurnButtonSprite = assets->getSprite("end_turn_button");
	std::unique_ptr<UIObject> endTurnButton(new Button(
		endTurnButtonSprite, glm::vec2{
			viewport.getLeft() + endTurnButtonSprite->getWidth() / 2.0f,
			viewport.getBottom() + endTurnButtonSprite->getHeight() / 2.0f
		}
	));
	endTurnButton->setOnPress(std::bind(&Scenario::endTurn, scenario));
	uiRoot->addChild(endTurnButton);
}

