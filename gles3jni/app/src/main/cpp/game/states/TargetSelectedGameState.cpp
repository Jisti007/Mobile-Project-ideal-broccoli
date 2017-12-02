#include "TargetSelectedGameState.h"

TargetSelectedGameState::TargetSelectedGameState(
	Game* game, Unit* selectedUnit, Unit* target)
	: UnitSelectedGameState(game, selectedUnit) {
	this->target = target;
	createUI();
}

void TargetSelectedGameState::recreateUI() {
	PlayerGameState::recreateUI();
	createUI();
}

void TargetSelectedGameState::createUI() {
	auto skills = selectedUnit->getType()->getValidSkills(selectedUnit, target);
	if (skills.size() == 1) {
		auto sprite = skills[0]->getSprite();
		auto map = target->getMap();
		/*
		std::unique_ptr<UIObject> skill(new UISprite(
			sprite, target->getActor()->getPosition() - map->getCamera()->getPosition() * GameMap::gridSize
		));
		uiRoot->addChild(skill);
		*/
		uiRoot->addNewChild<UISprite>(
			sprite, target->getActor()->getPosition() - map->getCamera()->getPosition() * GameMap::gridSize
		);
	}
}

void TargetSelectedGameState::move(float dx, float dy) {
	game->changeToNew<UnitSelectedGameState>(game, selectedUnit);
}
