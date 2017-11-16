#include <sstream>
#include "MapGameState.h"
#include "../ui/Button.h"
#include "../events/Movement.h"
#include "../ui/Label.h"

MapGameState::MapGameState(Game* game)
	: GameState(game) {
	auto assets = game->getAssets();
	auto map = game->getCampaign()->getScenario()->getActiveMap();
	auto viewport = game->getPipeline()->getViewport();

	auto buttonSprite = assets->getSprite("test_button");
	std::unique_ptr<UIObject> button(new Button(
		buttonSprite, glm::vec2{
			viewport.getLeft() + buttonSprite->getWidth() / 2.0f,
			viewport.getTop() - buttonSprite->getHeight() / 2.0f
		}
	));
	button->setOnPress(std::bind(&GameMap::generate, map));
	uiRoot->addChild(button);

	auto resourceSprite = assets->getSprite("ui_resource");
	auto resourceInfo = new UISprite(
		resourceSprite, glm::vec2{
			0, viewport.getTop() - resourceSprite->getHeight() / 2.0f
		}
	);
	std::unique_ptr<UIObject> resourceInfoPointer(resourceInfo);
	uiRoot->addChild(resourceInfoPointer);

	resourceLabel = new Label(
		u8"609", assets->getFont("default"),
		glm::vec2{resourceInfo->getLeft() + 50, viewport.getTop() - resourceSprite->getHeight() / 2.0f},
		glm::vec2{400,200}
	);
	std::unique_ptr<UIObject> resourceLabelPointer(resourceLabel);
	resourceInfo->addChild(resourceLabelPointer);

	// TODO: Make a system for displaying all non-hardcoded resources the active player possesses.

	auto playerResources = game->getCampaign()->getScenario()->getPlayerFaction()->getResources();

	int resourceOffset = 50;
	for (auto const& playerResource : playerResources)
	{
		auto resourceUISprite = playerResource.first->getSprite();

		auto resourceIcon = new UISprite(
			resourceUISprite, glm::vec2{resourceInfo->getLeft() + resourceOffset, viewport.getTop() - resourceSprite->getHeight() / 2.0f}, 0.4f);
		std::unique_ptr<UIObject> resourceIconPointer(resourceIcon);
		resourceLabel->addChild(resourceIconPointer);
		resourceOffset += 175;
	}

}

MapGameState::~MapGameState() {

}

void MapGameState::update(float deltaTime) {
	auto scenario = game->getCampaign()->getScenario();
	if (animatingEvent) {
		if (fastAnimation) {
			deltaTime *= 16;
		}
		if (animatingEvent->animate(deltaTime)) {
			scenario->popAnimation();
			animatingEvent = nullptr;
		}
	} else if (scenario->getAnimationCount() > 0) {
		animatingEvent = scenario->peekAnimation();
		animatingEvent->beginAnimation();
	}
	updateResourceUI();
}

void MapGameState::draw(Pipeline* pipeline) {
	auto map = game->getCampaign()->getScenario()->getActiveMap();
	map->draw();
	if (pressedHex != nullptr) {
		auto hexMarkerSprite = game->getAssets()->getSprite("hex_marker");
		auto position = map->getScreenPosition(pressedHex->getPosition());
		pipeline->draw(hexMarkerSprite, position, 1.0f);
	}
	GameState::draw(pipeline);
}

void MapGameState::move(float dx, float dy) {
	auto camera = game->getCampaign()->getScenario()->getActiveMap()->getCamera();
	auto zoom = camera->getZoom();
	dx /= zoom;
	dy /= zoom;
	camera->moveBy({dx, dy});
}

bool MapGameState::press(float x, float y) {
	if (GameState::press(x, y)) {
		return true;
	}

	if (animatingEvent != nullptr) {
		fastAnimation = true;
		return true;
	}

	auto scenario = game->getCampaign()->getScenario();
	auto activeFaction = scenario->getActiveFaction();
	if (!activeFaction->isPlayer()) {
		return true;
	}

	auto map = scenario->getActiveMap();
	auto gridPosition = map->getGridPosition({x, y});
	auto hex = map->tryGetHex(gridPosition);
	if (hex != nullptr) {
		pressedHex = hex;
		auto unit = hex->getUnit();
		if (unit != nullptr) {
			if (unit->getFaction() == activeFaction) {
				selectedUnit = unit;
			}
		} else if (selectedUnit != nullptr) {
			auto selectedUnitHex = map->tryGetHex(selectedUnit->getGridPosition());
			auto path = selectedUnitHex->findShortestPath(hex, selectedUnit);
			std::unique_ptr<ScenarioEvent> movement(new Movement(
				selectedUnit, path
			));
			scenario->executeEvent(movement);
			fastAnimation = false;
		}
	}

	return true;
}

void MapGameState::updateResourceUI() {
	auto resources = game->getCampaign()->getScenario()->getPlayerFaction()->getResources();
	auto gold = game->getAssets()->getResource("gold");
	auto food = game->getAssets()->getResource("food");
	auto material = game->getAssets()->getResource("material");
	auto crystal = game->getAssets()->getResource("crystal");

	int goldAmount = resources[gold];
	int foodAmount = resources[food];
	int materialAmount = resources[material];
	int crystalAmount = resources[crystal];

	std::stringstream resourceString;
	resourceString << "G: " << goldAmount << " F: " << foodAmount << " M: " << materialAmount << " C: " << crystalAmount;

	resourceLabel->setText(resourceString.str().c_str());
}
