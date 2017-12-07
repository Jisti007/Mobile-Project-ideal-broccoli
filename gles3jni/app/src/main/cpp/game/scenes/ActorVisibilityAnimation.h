#ifndef GLES3JNI_ACTORSPAWNANIMATION_H
#define GLES3JNI_ACTORSPAWNANIMATION_H

#include "Animation.h"
#include "Actor.h"

class ActorVisibilityAnimation : public Animation {
public:
	ActorVisibilityAnimation(Actor* actor, bool visible, bool blocking = true);

	virtual bool onAnimate(float deltaTime);

private:
	Actor* actor;
	bool visible;
};

#endif //GLES3JNI_ACTORSPAWNANIMATION_H
