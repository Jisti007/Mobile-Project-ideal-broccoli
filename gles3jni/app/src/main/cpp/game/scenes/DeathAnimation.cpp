#include "DeathAnimation.h"

DeathAnimation::DeathAnimation(Actor* actor, Scene* scene, bool blocking)
	: Animation(blocking) {
	this->actor = actor;
	this->scene = scene;
}

bool DeathAnimation::onAnimate(float deltaTime) {
	scene->removeActor(actor);
	return true;
}
