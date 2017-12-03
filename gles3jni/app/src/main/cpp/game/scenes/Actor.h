#ifndef GLES3JNI_ACTOR_H
#define GLES3JNI_ACTOR_H

#include "../../glm/glm.hpp"
#include "../Sprite.h"
#include "../Pipeline.h"

class Actor {
public:
	Actor(Sprite* sprite, glm::vec2 position, float depth, int layer);

	virtual void draw(Pipeline* pipeline);

	inline void setPosition(glm::vec2 position) { this->position = position; }
	inline void offsetPosition(glm::vec2 delta) { this->position += delta; }
	inline glm::vec2 getPosition() { return position; }
	inline Sprite* getSprite() { return sprite; }
	inline void setSprite(Sprite* sprite) { this->sprite = sprite; }
	inline float getDepth() { return depth; }
	inline void setDepth(float depth) { this->depth = depth; }
	inline int getLayer() { return layer; }

private:
	Sprite* sprite;
	glm::vec2 position;
	float depth = 0.0f;
	int layer;
};

struct ActorSorter {
	inline bool operator() (Actor* a, Actor* b) {
		if (a->getLayer() < b->getLayer()) {
			return true;
		}
/*
		if (a->getSprite()->getTexture() < b->getSprite()->getTexture()) {
			return true;
		}
*/
		return a->getDepth() < b->getDepth();
	}
};

#endif //GLES3JNI_ACTOR_H
