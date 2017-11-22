#include "DeathAnimation.h"

DeathAnimation::DeathAnimation(Actor* actor, Scene* scene) {
	this->actor = actor;
	this->scene = scene;
}

bool DeathAnimation::animate(float deltaTime) {
	scene->removeActor(actor);
	return true;
}
