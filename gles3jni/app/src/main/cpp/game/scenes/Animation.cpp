#include "Animation.h"

Animation::Animation(bool blocking) {
	this->blocking = blocking;
}

bool Animation::animate(float deltaTime) {
	if (!finished) {
		finished = onAnimate(deltaTime);
	}
	if (finished) {
		if (next) {
			return next->animate(deltaTime);
		} else {
			return finished;
		}
	}

	return false;
}
