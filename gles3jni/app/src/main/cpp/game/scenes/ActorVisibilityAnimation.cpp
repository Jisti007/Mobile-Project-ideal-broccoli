#include "ActorVisibilityAnimation.h"

ActorVisibilityAnimation::ActorVisibilityAnimation(
	Actor* actor, bool visible, bool blocking
) : Animation(blocking) {
	this->actor = actor;
	this->visible = visible;
}

bool ActorVisibilityAnimation::onAnimate(float deltaTime) {
	actor->setVisible(visible);
	return true;
}
