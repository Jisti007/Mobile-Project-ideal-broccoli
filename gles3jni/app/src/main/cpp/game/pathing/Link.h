#ifndef GLES3JNI_LINK_H
#define GLES3JNI_LINK_H

class Node;

#include "Node.h"
#include "Agent.h"
#include <vector>
#include <memory>

/// An abstract way to get from the source to the destination Node.
class Link {
public:
	Link(Node* source, Node* destination);
	virtual ~Link();

	virtual float getCost(Agent* agent, float pathCost) = 0;

	inline Node* getSource() { return source; }
	inline Node* getDestination() { return destination; }

protected:
	Node* source;
	Node* destination;
};

/// Constant cost for all agents.
class SimpleLink : public Link {
public:
	SimpleLink(Node* source, Node* destination, float cost);
	virtual ~SimpleLink();

	virtual float getCost(Agent* agent, float pathCost) { return cost; }

private:
	float cost;
};

#endif //GLES3JNI_LINK_H
