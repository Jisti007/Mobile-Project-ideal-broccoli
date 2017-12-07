#include "Skill.h"
#include "Unit.h"
#include "scenes/MovementAnimation.h"
#include "scenes/DeathAnimation.h"
#include "scenes/ActorVisibilityAnimation.h"

HPModification::HPModification(int amount) {
	this->amount = amount;
}

void HPModification::apply(SkillUser* user, SkillTarget* target) {
	auto targetUnit = static_cast<Unit*>(target);
	targetUnit->modifyHP(amount);
}

float HPModification::evaluate(SkillUser* user, SkillTarget* target, float cost) {
	auto userUnit = static_cast<Unit*>(user);
	auto targetUnit = static_cast<Unit*>(target);
	if (userUnit->isFriendlyTowards(targetUnit)) {
		return amount / cost;
	}
	return -amount / cost;
}

SourceDestination::SourceDestination(
	SkillAnimation::Role source,
	SkillAnimation::Role destination
) {
	this->source = source;
	this->destination = destination;
}

Actor* SourceDestination::getSourceActor(SkillUser* user, SkillTarget* target) {
	switch (source) {
		case SkillAnimation::user:
			return user->getActor();
		case SkillAnimation::target:
			return target->getActor();
	}
}

Actor* SourceDestination::getDestinationActor(SkillUser* user, SkillTarget* target) {
	switch (destination) {
		case SkillAnimation::user:
			return user->getActor();
		case SkillAnimation::target:
			return target->getActor();
	}
}

Nudge::Nudge(
	SkillAnimation::Role source, SkillAnimation::Role destination, float distance
) : SourceDestination(
	source, destination
){
	this->distance = distance;
}

void Nudge::queue(SkillUser* user, SkillTarget* target) {
	auto userUnit = static_cast<Unit*>(user);
	auto map = userUnit->getMap();
	auto scene = map->getScene();
	auto sourceActor = getSourceActor(user, target);
	auto originalPosition = map->getScreenPosition(user->getGridPosition());
	auto destinationActor = getDestinationActor(user, target);
	auto delta = destinationActor->getPosition() - originalPosition;
	auto direction = glm::normalize(delta);
	auto distance = sqrtf(glm::dot(delta, delta));
	auto destinationPosition = originalPosition + this->distance * distance * direction;
	auto first = scene->queueNew<MovementAnimation>(sourceActor, destinationPosition, 2.0f, false);
	first->chainNew<MovementAnimation>(sourceActor, originalPosition);
}

Projectile::Projectile(
	Sprite* sprite, SkillAnimation::Role source,
	SkillAnimation::Role destination, float speed
) : SourceDestination(
	source, destination
) {
	this->sprite = sprite;
	this->source = source;
	this->destination = destination;
	this->speed = speed;
}

void Projectile::queue(SkillUser* user, SkillTarget* target) {
	auto userUnit = static_cast<Unit*>(user);
	auto map = userUnit->getMap();
	auto scene = map->getScene();
	auto sourceActor = getSourceActor(user, target);
	auto sourcePosition = map->getScreenPosition(userUnit->getGridPosition());
	auto destinationActor = getDestinationActor(user, target);
	auto projectile = scene->addNew<Actor>(sprite, sourcePosition, 1.0f, PROJECTILE_LAYER, false);
	scene->queueNew<ActorVisibilityAnimation>(projectile, true, PROJECTILE_LAYER);
	scene->queueNew<MovementAnimation>(projectile, destinationActor->getPosition(), speed);
	scene->queueNew<DeathAnimation>(projectile, scene);
}

Skill::Skill(
	Sprite* sprite, std::string name, std::string description, TargetType targetType, int range, float cost,
	EffectList& effects, AnimationList& animations
) {
	this->sprite = sprite;
	this->name = name;
	this->description = description;
	this->targetType = targetType;
	this->range = range;
	this->cost = cost;
	this->effects = std::move(effects);
	this->animations = std::move(animations);
}

void Skill::use(SkillUser* user, SkillTarget* target) {
	for (auto& animation : animations) {
		animation->queue(user, target);
	}
	for (auto& effect : effects) {
		effect->apply(user, target);
	}
	auto userUnit = static_cast<Unit*>(user);
	userUnit->modifyMovement(-getCost());
}

float Skill::evaluate(SkillUser* user, SkillTarget* target, float extraCost) {
	float evaluation = 0.0f;
	for (auto& effect : effects) {
		evaluation += effect->evaluate(user, target, cost + extraCost);
	}
	return evaluation;
}

bool Skill::validate(SkillUser* user, SkillTarget* target, float extraCost) {
	auto targetUnit = dynamic_cast<Unit*>(target);
	if (!targetUnit) {
		return false;
	}

	auto userUnit = static_cast<Unit*>(user);
	if (userUnit->getMovement() < getCost() + extraCost) {
		return false;
	}

	switch (targetType) {
		case TargetType::unit:
			return  true;
		case enemy:
			return userUnit->isHostileTowards(targetUnit);
		case friendly:
			return userUnit->isFriendlyTowards(targetUnit);
		case hex:
			return false;
	}

	return false;
}

bool Skill::validate(SkillUser* user, SkillTarget* target, float extraCost, int range) {
	if (range <= getRange()) {
		return validate(user, target, extraCost);
	}
	return false;
}
