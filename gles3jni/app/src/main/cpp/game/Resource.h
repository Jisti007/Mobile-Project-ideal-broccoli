#ifndef GLES3JNI_RESOURCETYPE_H
#define GLES3JNI_RESOURCETYPE_H

#include "Texture.h"
#include "Sprite.h"

class Resource {
public:
	Resource(Sprite* sprite, int priority);
	~Resource();

	inline Sprite* getSprite() { return sprite; }
	inline const int getPriority() const { return priority; }

private:
	Sprite* sprite;
	int priority;
};

typedef std::pair<Resource*, int> ResourceAmount;

struct ResourceSorter {
	inline bool operator() (const Resource* struct1, const Resource* struct2)
	{
		return (struct1->getPriority() < struct2->getPriority());
	}
};
#endif //GLES3JNI_RESOURCETYPE_H
