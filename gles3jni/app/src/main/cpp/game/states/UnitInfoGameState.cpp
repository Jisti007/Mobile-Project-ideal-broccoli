#include "UnitInfoGameState.h"

UnitInfoGameState::UnitInfoGameState(Game* game, Unit* selectedUnit) : PlayerGameState(game) {
	this->selectedUnit = selectedUnit;
	createUI();
}

void UnitInfoGameState::recreateUI() {
	PlayerGameState::recreateUI();
	createUI();
}

void UnitInfoGameState::createUI() {
	auto assets = game->getAssets();
	auto viewport = game->getPipeline()->getViewport();

	auto infoPanelSprite = assets->getSprite("ui_info");
	auto infoPanel = uiRoot->addNewChild<InfoPanel>(
		infoPanelSprite, glm::vec2{
			0, 0
		},
		assets->getFont("default"),
		assets,
		game
	);
	infoPanel->updateInfo(selectedUnit);
}

void UnitInfoGameState::move(float dx, float dy) {
	game->popState();
}

bool UnitInfoGameState::press(float x, float y) {
	if (GameState::press(x, y)) {
		return true;
	}
	game->popState();
	return true;
}

void UnitInfoGameState::zoom(float scaleFactor) {
	game->popState();
}


