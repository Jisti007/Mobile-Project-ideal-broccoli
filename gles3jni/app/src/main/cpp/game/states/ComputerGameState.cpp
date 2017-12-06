#include "ComputerGameState.h"

ComputerGameState::ComputerGameState(Game* game) : AnimationGameState(game) {

}

void ComputerGameState::update(float deltaTime) {
	Unit* unit = pickUnit();
	if (unit != nullptr) {
		auto maxRange = unit->getType()->getMaxSkillRange();
		auto nodes = unit->getHex()->findAllNodes(unit, unit->getMovement());
		SkillUsage best{nullptr, unit, nullptr, Path(), 0};
		for (auto& node : nodes) {
			auto path = unit->getHex()->buildPath(node, unit);
			best = getBestSkill(unit, path, maxRange, best);
		}
		if (best.skill && best.target) {
			unit->move(best.path);
			best.skill->use(unit, best.target);
		} else {
			unit->endTurn();
		}
	}

	AnimationGameState::update(deltaTime);
}

Unit* ComputerGameState::pickUnit() {
	auto scenario = game->getCampaign()->getScenario();
	auto faction = scenario->getActiveFaction();
	for (auto& unit : scenario->getActiveMap()->getUnits()) {
		if (unit->getFaction() == faction && unit->isMovable()) {
			return unit.get();
		}
	}
	return nullptr;
}

SkillUsage ComputerGameState::getBestSkill(Unit* unit, Path& path, int maxRange, SkillUsage currentBest) {
	auto hex = static_cast<MapHex*>(path.getLinks().back()->getDestination());
	if (hex->getUnit() != nullptr) {
		return currentBest;
	}

	auto potentialTargets = unit->getHex()->getHexesWithin(maxRange);
	for (auto& potentialTarget : potentialTargets) {
		auto potentialTargetUnit = potentialTarget->getUnit();
		for (auto& skill : unit->getType()->getSkills()) {
			currentBest = getBestSkill(unit, path, potentialTarget, skill.get(), currentBest);
			if (potentialTargetUnit != nullptr) {
				currentBest = getBestSkill(unit, path, potentialTargetUnit, skill.get(), currentBest);
			}
		}
	}
	return currentBest;
}

SkillUsage ComputerGameState::getBestSkill(Unit* unit, Path& path, MapObject* target, Skill* skill, SkillUsage currentBest) {
	if (skill->validate(unit, target, path.getCost())) {
		auto evaluation = skill->evaluate(unit, target, path.getCost());
		if (evaluation > currentBest.evaluation) {
			return {skill, unit, target, path, evaluation};
		}
	}
	return currentBest;
}

void ComputerGameState::onAnimationFinished() {
	//game->getCampaign()->getScenario()->endTurn();
}
