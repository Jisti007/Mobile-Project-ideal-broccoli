#ifndef GLES3JNI_DEATHANIMATION_H
#define GLES3JNI_DEATHANIMATION_H

#include "Animation.h"
#include "Actor.h"
#include "Scene.h"

class DeathAnimation : public Animation {
public:
	DeathAnimation(Actor* actor, Scene* scene, bool blocking = true);

protected:
	virtual bool onAnimate(float deltaTime);

private:
	Actor* actor;
	Scene* scene;
};

#endif //GLES3JNI_DEATHANIMATION_H
