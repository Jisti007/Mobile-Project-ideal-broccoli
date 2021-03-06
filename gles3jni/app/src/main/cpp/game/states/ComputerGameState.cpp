#include "ComputerGameState.h"

ComputerGameState::ComputerGameState(Game* game) : AnimationGameState(game) {

}

void ComputerGameState::update(float deltaTime) {
	auto scenario = game->getCampaign()->getScenario();
	auto faction = scenario->getActiveFaction();
	for (auto& unitPtr : scenario->getActiveMap()->getUnits()) {
		auto unit = unitPtr.get();
		if (unit == nullptr || unit->getFaction() != faction) {
			continue;
		}

		while (unit->isMovable()) {
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
				auto hexWithEnemy = [&unit](Node* node){
					auto hex = static_cast<MapHex*>(node);
					auto hexUnit = hex->getUnit();
					return hexUnit != nullptr && unit->isHostileTowards(hexUnit);
				};
				auto path = unit->getHex()->findNearest(unit, hexWithEnemy);
				unit->move(path);
				unit->endTurn();
			}
		}
	}

	AnimationGameState::update(deltaTime);
}

SkillUsage ComputerGameState::getBestSkill(Unit* unit, Path& path, int maxRange, SkillUsage currentBest) {
	MapHex* hex;
	if (path.getLinks().size() > 0) {
		hex = static_cast<MapHex*>(path.getLinks().back()->getDestination());
		if (hex->getUnit() != nullptr) {
			return currentBest;
		}
	} else {
		hex = unit->getHex();
	}

	auto potentialTargets = hex->getHexesWithin(maxRange);
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
	MapHex* hex;
	if (path.getLinks().size() > 0) {
		hex = static_cast<MapHex*>(path.getLinks().back()->getDestination());
	} else {
		hex = unit->getHex();
	}

	if (skill->validate(unit, target, path.getCost(), hex->getDistance(target))) {
		auto evaluation = skill->evaluate(unit, target, path.getCost());
		if (evaluation > currentBest.evaluation) {
			return {skill, unit, target, path, evaluation};
		}
	}
	return currentBest;
}

void ComputerGameState::onAnimationFinished() {
	game->getCampaign()->getScenario()->endTurn();
}
