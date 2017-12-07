#include "UnitInfoGameState.h"

UnitInfoGameState::UnitInfoGameState(Game* game, Unit* selectedUnit) : PlayerGameState(game) {
	this->selectedUnit = selectedUnit;
}

void UnitInfoGameState::createInfo(Unit* selectedUnit) {
	auto assets = game->getAssets();
	auto viewport = game->getPipeline()->getViewport();

	auto infoPanelSprite = assets->getSprite("ui_info");
	infoPanel = uiRoot->addNewChild<InfoPanel>(
		infoPanelSprite, glm::vec2{
			0, viewport.getTop() - infoPanelSprite->getHeight() / 2.0f
		},
		assets->getFont("default"),
	    assets
	);
	infoPanel->updateInfo(selectedUnit);
}


