#include "UnitSelectedGameState.h"
#include "../events/Attack.h"
#include "AnimationGameState.h"
#include "PathSelectedGameState.h"
#include "TargetSelectedGameState.h"
#include "UnitInfoGameState.h"

UnitSelectedGameState::UnitSelectedGameState(Game* game, Unit* selectedUnit) : IdleGameState(game) {
	this->selectedUnit = selectedUnit;
	createUI();
}

void UnitSelectedGameState::recreateUI() {
	IdleGameState::recreateUI();
	createUI();
}

void UnitSelectedGameState::createUI() {
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
		&UnitSelectedGameState::exitStateButton_onPress, this,std::placeholders::_1));
}

void UnitSelectedGameState::exitStateButton_onPress(void* args) {
	game->changeToNew<IdleGameState>(game);
}

void UnitSelectedGameState::onPressHex(MapHex* pressedHex) {
	auto scenario = game->getCampaign()->getScenario();
	auto activeFaction = scenario->getActiveFaction();
	auto map = scenario->getActiveMap();
	auto unit = pressedHex->getUnit();
	if (unit != nullptr) {
		if (unit == selectedUnit) {
			game->pushNew<UnitInfoGameState>(game, selectedUnit);
		}
		else if (unit->getFaction() != activeFaction) {
			game->changeToNew<TargetSelectedGameState>(game, selectedUnit, unit);
		} else {
			game->changeToNew<UnitSelectedGameState>(game, unit);
		}
	} else {
		auto selectedUnitHex = map->tryGetHex(selectedUnit->getGridPosition());
		auto path = selectedUnitHex->findShortestPath(pressedHex, selectedUnit);
		game->changeToNew<PathSelectedGameState>(game, path, selectedUnit);
	}
}

