#ifndef GLES3JNI_LINK_H
#define GLES3JNI_LINK_H

class Node;

#include "Node.h"
#include "Agent.h"

class Link {
public:
	Link(Node* source, Node* destination);
	~Link();

	virtual float getCost(Agent* agent) = 0;

	inline Node* getSource() { return source; }
	inline Node* getDestination() { return destination; }

private:
	Node* source;
	Node* destination;
};

#endif //GLES3JNI_LINK_H
