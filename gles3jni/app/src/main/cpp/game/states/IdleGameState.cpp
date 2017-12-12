#include "IdleGameState.h"
#include "../ui/Button.h"
#include "../ui/UITexture.h"

IdleGameState::IdleGameState(Game* game) : PlayerGameState(game) {
	createUI();
}

void IdleGameState::recreateUI() {
	PlayerGameState::recreateUI();
	createUI();
}

void IdleGameState::createUI() {
	auto assets = game->getAssets();
	auto scenario = game->getCampaign()->getScenario();
	auto viewport = game->getPipeline()->getViewport();
	auto endTurnButtonSprite = assets->getSprite("end_turn_button");
	auto endTurnButton = uiRoot->addNewChild<Button>(
		endTurnButtonSprite, glm::vec2{
			viewport.getLeft() + endTurnButtonSprite->getWidth() / 2.0f,
			viewport.getBottom() + endTurnButtonSprite->getHeight() / 2.0f
		}
	);
	endTurnButton->setOnPress(std::bind(&Scenario::endTurn, scenario));
}
