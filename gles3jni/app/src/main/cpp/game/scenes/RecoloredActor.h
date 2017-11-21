#ifndef GLES3JNI_RECOLOREDACTOR_H
#define GLES3JNI_RECOLOREDACTOR_H

#include "Actor.h"

class RecoloredActor : public Actor {
public:
	RecoloredActor(Sprite* sprite, glm::vec2 position, float depth, std::vector<glm::vec3> colors);

	virtual void draw(Pipeline* pipeline);

private:
	std::vector<glm::vec3> colors;
};

#endif //GLES3JNI_RECOLOREDACTOR_H
