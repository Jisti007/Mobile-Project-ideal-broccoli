#ifndef GLES3JNI_NODE_H
#define GLES3JNI_NODE_H

class Link;

#include "Comparable.h"
#include "Agent.h"
#include "Link.h"
#include <list>
#include <vector>
#include <cstdio>
#include <memory>

enum NodeStatus {
	unvisited,
	open,
	closed
};

class Node : public Comparable {
public:
	Node();
	virtual ~Node();

	virtual float getHeuristic(Node* destination) = 0;
	virtual int compareTo(Comparable* other);
	std::list<Link*> findShortestPath(Node* destination, Agent* agent, size_t graphSize = 128);

protected:
	std::vector<std::unique_ptr<Link>> links;

private:
	Link* pathLink = nullptr;
	NodeStatus status = NodeStatus::unvisited;
	uint64_t lastVisit = 0;
	float pathCost = 0.0f;
	float heuristic = 0.0f;
};

#endif //GLES3JNI_NODE_H
