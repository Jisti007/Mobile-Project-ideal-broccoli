#ifndef GLES3JNI_NODE_H
#define GLES3JNI_NODE_H

class Link;

#include "Comparable.h"
#include "Agent.h"
#include "Link.h"
#include <list>
#include <vector>
#include <cstdio>

enum NodeStatus {
	unvisited,
	open,
	closed
};

class Node : public Comparable {
public:
	virtual std::vector<Link> getLinks() = 0;
	virtual float getHeuristic(Node* destination) = 0;

	std::list<Node*> findShortestPath(Node* destination, Agent* agent);

	virtual int compareTo(Comparable* other);

private:
	Node* previous = nullptr;
	NodeStatus status = NodeStatus::unvisited;
	uint64_t lastVisit = 0;
	float pathCost = 0.0f;
	float heuristic = 0.0f;
};

#endif //GLES3JNI_NODE_H
