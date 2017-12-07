#ifndef GLES3JNI_MOVEMENTANIMATION_H
#define GLES3JNI_MOVEMENTANIMATION_H

#include "Animation.h"
#include "Actor.h"
#include "Scene.h"

class MovementAnimation : public Animation {
public:
	MovementAnimation(
		Actor* actor, Scene* scene, glm::vec2 destination,
		bool follows, float speed = 2.0f, bool blocking = true
	);

protected:
	virtual bool onAnimate(float deltaTime);

private:
	Actor* actor;
	Scene* scene;
	glm::vec2 destination;
	float speed;
	bool follows;
};

#endif //GLES3JNI_MOVEMENTANIMATION_H
