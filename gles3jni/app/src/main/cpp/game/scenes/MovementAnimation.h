#ifndef GLES3JNI_MOVEMENTANIMATION_H
#define GLES3JNI_MOVEMENTANIMATION_H

#include "Animation.h"
#include "Actor.h"

class MovementAnimation : public Animation {
public:
	MovementAnimation(Actor* actor, glm::vec2 destination, float speed = 2.0f, bool blocking = true);

protected:
	virtual bool onAnimate(float deltaTime);

private:
	Actor* actor;
	glm::vec2 destination;
	float speed;
};

#endif //GLES3JNI_MOVEMENTANIMATION_H
