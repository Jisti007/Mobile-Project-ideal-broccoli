#include "TargetSelectedGameState.h"
#include "AnimationGameState.h"

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
	skills = selectedUnit->getType()->getValidSkills(selectedUnit, target);
	if (skills.size() == 1) {
		auto skill = skills[0];
		auto sprite = skill->getSprite();
		auto map = target->getMap();
		auto skillButton = uiRoot->addNewChild<UISprite>(
			sprite, target->getActor()->getPosition() - map->getCamera()->getPosition() * GameMap::gridSize
		);
		skillButton->setOnPress(
			std::bind(&TargetSelectedGameState::skillButton_onPress, this, std::placeholders::_1
		));
		skillButton->setOnPressArgs(skill);
	}
}

void TargetSelectedGameState::move(float dx, float dy) {
	game->changeToNew<UnitSelectedGameState>(game, selectedUnit);
}

void TargetSelectedGameState::skillButton_onPress(void* skillArg) {
	auto skill = static_cast<Skill*>(skillArg);
	skill->use(selectedUnit, target);
	game->changeToNew<AnimationGameState>(game, selectedUnit);
}
