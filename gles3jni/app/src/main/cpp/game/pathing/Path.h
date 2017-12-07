#ifndef GLES3JNI_PATH_H
#define GLES3JNI_PATH_H

class Node;

#include "Link.h"
#include <list>

class Path {
public:
	Path();
	Path(std::list<Link*> links, Agent* agent);

	//void shorten(float maxCost);
	void popLast();

	inline std::list<Link*>& getLinks() { return links; }
	inline Agent* getAgent() { return agent; }
	inline float getCost() { return cost; }

private:
	std::list<Link*> links;
	Agent* agent;
	float cost = 0.0f;
};

#endif //GLES3JNI_PATH_H
