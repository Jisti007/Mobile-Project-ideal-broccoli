#ifndef GLES3JNI_ACTOR_H
#define GLES3JNI_ACTOR_H

#include "../../glm/glm.hpp"
#include "../Sprite.h"
#include "../Pipeline.h"

const int HEX_LAYER = 0;
const int DECORATION_LAYER= 1;
const int BUILDING_LAYER = 2;
const int UNIT_LAYER = 3;
const int PROJECTILE_LAYER = 4;

class Actor {
public:
	Actor(Sprite* sprite, glm::vec2 position, float depth, int layer, bool visible = true);

	virtual void draw(Pipeline* pipeline);

	inline Sprite* getSprite() { return sprite; }
	inline void setSprite(Sprite* sprite) { this->sprite = sprite; }
	inline glm::vec2 getPosition() { return position; }
	inline void setPosition(glm::vec2 position) { this->position = position; }
	inline void offsetPosition(glm::vec2 delta) { this->position += delta; }
	inline glm::vec4 getColor() { return color; }
	inline void setColor(glm::vec4 color) { this->color = color; }
	inline float getDepth() { return depth; }
	inline void setDepth(float depth) { this->depth = depth; }
	inline int getLayer() { return layer; }
	inline bool isVisible() { return visible; }
	inline void setVisible(bool visible) { this->visible = visible; }

private:
	Sprite* sprite;
	glm::vec2 position;
	glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
	float depth = 0.0f;
	int layer;
	bool visible;
};

struct ActorSorter {
	inline bool operator() (Actor* a, Actor* b) {
		if (a->getLayer() < b->getLayer()) {
			return true;
		} else if (a->getLayer() == b->getLayer()) {
			return a->getDepth() < b->getDepth();
		}
		/*
		if (a->getSprite()->getTexture() < b->getSprite()->getTexture()) {
			return true;
		}
		*/
		return false;
	}
};

#endif //GLES3JNI_ACTOR_H
