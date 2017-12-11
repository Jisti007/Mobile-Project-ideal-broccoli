#include "BuildingSelectedGameState.h"
#include "BuildingInfoGameState.h"

BuildingSelectedGameState::BuildingSelectedGameState(Game* game, Building* selectedBuilding) : IdleGameState(game) {
	this->selectedBuilding = selectedBuilding;
	createUI();
}

void BuildingSelectedGameState::onPressHex(MapHex* pressedHex) {
	auto scenario = game->getCampaign()->getScenario();
	//auto activeFaction = scenario->getActiveFaction();
	//auto map = scenario->getActiveMap();
	auto building = pressedHex->getBuilding();
	if (building != nullptr){
		if (building == selectedBuilding) {
			game->pushNew<BuildingInfoGameState>(game, selectedBuilding);
		}
	}
}

void BuildingSelectedGameState::recreateUI() {
	IdleGameState::recreateUI();
	createUI();
}

void BuildingSelectedGameState::createUI() {
	auto assets = game->getAssets();
	auto viewport = game->getPipeline()->getViewport();

	auto exitStateSprite = assets->getSprite("no_button");
	auto exitStateButton = uiRoot->addNewChild<Button>(
		exitStateSprite, glm::vec2{
			viewport.getLeft() + exitStateSprite->getWidth() / 2.0f,
			viewport.getBottom() + viewport.getTop()
		}
	);
	exitStateButton->setOnPress(std::bind(
		&BuildingSelectedGameState::exitStateButton_onPress, this,std::placeholders::_1));
}

void BuildingSelectedGameState::exitStateButton_onPress(void* args) {
	game->changeToNew<IdleGameState>(game);
}
