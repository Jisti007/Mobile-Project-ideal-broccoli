#ifndef GLES3JNI_MOVEMENTANIMATION_H
#define GLES3JNI_MOVEMENTANIMATION_H

#include "Animation.h"
#include "Actor.h"

class MovementAnimation : public Animation {
public:
	MovementAnimation(Actor* actor, glm::vec2 destination);
	virtual bool animate(float deltaTime);

private:
	Actor* actor;
	glm::vec2 destination;
};

#endif //GLES3JNI_MOVEMENTANIMATION_H
