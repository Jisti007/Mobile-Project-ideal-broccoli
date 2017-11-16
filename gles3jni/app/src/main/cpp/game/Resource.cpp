#include "Resource.h"

Resource::Resource(Sprite* sprite, int priority) {
	this->sprite = sprite;
	this->priority = priority;
}

Resource::~Resource() {

}
