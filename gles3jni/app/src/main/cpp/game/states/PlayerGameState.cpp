#include "PlayerGameState.h"
#include "UnitSelectedGameState.h"
#include "../ui/RecoloredUISprite.h"
#include "../ui/Button.h"
#include "BuildingSelectedGameState.h"

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

}

void PlayerGameState::onPressHex(MapHex* hex) {
	auto scenario = game->getCampaign()->getScenario();
	auto activeFaction = scenario->getActiveFaction();
	auto unit = hex->getUnit();
	auto building = hex->getBuilding();
	if (unit != nullptr && unit->getFaction() == activeFaction) {
		game->changeToNew<UnitSelectedGameState>(game, unit);
	} else if (building != nullptr && building->getFaction() == activeFaction) {
		game->changeToNew<BuildingSelectedGameState>(game, building);
	}
}

void PlayerGameState::createUI() {
	auto assets = game->getAssets();
	auto scenario = game->getCampaign()->getScenario();
	//auto map = scenario->getActiveMap();
	auto viewport = game->getPipeline()->getViewport();

	auto resourcePanelSprite = assets->getSprite("ui_resource");
	resourcePanel = uiRoot->addNewChild<ResourcePanel>(
		resourcePanelSprite, glm::vec2{
			0, viewport.getTop() - resourcePanelSprite->getHeight() / 2.0f
		},
		assets->getFont("default")
	);
	resourcePanel->updateResources(scenario);

	auto crestSprite = assets->getSprite("faction_crest");
	auto colors = scenario->getActiveFaction()->getColors();
	uiRoot->addNewChild<RecoloredUISprite>(
		crestSprite,
		Transform2D{
			glm::vec2{
				0 - resourcePanelSprite->getWidth() / 2.0f - crestSprite->getWidth() / 2.0f,
				viewport.getTop() - crestSprite->getHeight() * 0.5f / 2.0f
			},
		    glm::vec2{0.5f, 0.5f}
		},
		colors
	);
}

