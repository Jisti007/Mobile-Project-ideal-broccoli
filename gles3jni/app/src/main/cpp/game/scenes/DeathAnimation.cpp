#include "DeathAnimation.h"

DeathAnimation::DeathAnimation(Actor* actor, Scene* scene, float duration, bool blocking)
	: Animation(blocking) {
	this->actor = actor;
	this->scene = scene;
	this->duration = duration;
}

bool DeathAnimation::onAnimate(float deltaTime) {
	auto color = actor->getColor();
	if (duration > 0) {
		color.a -= deltaTime / duration;
	} else {
		color.a = 0.0f;
	}
	actor->setColor(color);
	if (color.a <= 0) {
		scene->removeActor(actor);
		return true;
	}
	return false;
}
