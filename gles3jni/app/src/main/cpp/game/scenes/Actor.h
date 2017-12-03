#ifndef GLES3JNI_ACTOR_H
#define GLES3JNI_ACTOR_H

#include "../../glm/glm.hpp"
#include "../Sprite.h"
#include "../Pipeline.h"

class Actor {
public:
	Actor(Sprite* sprite, glm::vec2 position, float depth);

	virtual void draw(Pipeline* pipeline);

	inline void setPosition(glm::vec2 position) { this->position = position; }
	inline void offsetPosition(glm::vec2 delta) { this->position += delta; }
	inline glm::vec2 getPosition() { return position; }
	inline Sprite* getSprite() { return sprite; }
	inline void setSprite(Sprite* sprite) { this->sprite = sprite; }
	inline float getDepth() { return depth; }
	inline void setDepth(float depth) { this->depth = depth; }

private:
	Sprite* sprite;
	glm::vec2 position;
	float depth = 0.0f;
};

struct ActorSorter {
	inline bool operator() (Actor* actor1, Actor* actor2) {
		return (actor1->getDepth() < actor2->getDepth());
	}
};

struct ActorPointerSorter {
	inline bool operator() (std::unique_ptr<Actor>& actor1, std::unique_ptr<Actor>& actor2)
	{
		return (actor1->getDepth() > actor2->getDepth());
	}
};

#endif //GLES3JNI_ACTOR_H
