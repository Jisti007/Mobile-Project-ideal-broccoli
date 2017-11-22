#ifndef GLES3JNI_NODE_H
#define GLES3JNI_NODE_H

class Link;

#include "Comparable.h"
#include "Agent.h"
#include "Link.h"
#include "BinaryHeap.h"
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

	/// \return An estimate of how far the destination is from this node.
	virtual float getHeuristic(Node* destination) = 0;

	/// \param graphSize The estimated number of nodes traversed.
	std::list<Link*> findShortestPath(Node* destination, Agent* agent, size_t graphSize = 128);

	/// \param graphSize The estimated number of nodes traversed.
	std::vector<Node*> findAllNodes(Agent* agent, float maxPathCost, size_t graphSize = 128);

	/// Use this function with caution.
	/// It should only be called after pathfinding has finished and before it is called again.
	/// findShortestPath uses this function automatically,  but it can be useful after findAllNodes.
	/// You need to make sure the destination is one of the nodes returned.
	std::list<Link*> buildPath(Node* destination);

	int compareTo(Comparable* other);

protected:
	std::vector<std::unique_ptr<Link>> links;

private:
	Link* pathLink = nullptr;
	NodeStatus status = NodeStatus::unvisited;
	uint64_t lastVisit = 0;
	float pathCost = 0.0f;
	float heuristic = 0.0f;

	void initializePathfinder(BinaryHeap& openNodes, size_t graphSize);
	void visitNeighbors(BinaryHeap& openNodes, Agent* agent);
	void visitNeighbors(BinaryHeap& openNodes, Agent* agent, Node* destination);
	void tryReset();
	void tryOpen(BinaryHeap& openNodes, Link* link, Agent* agent);
	void tryReposition(BinaryHeap& openNodes, Link* link, Agent* agent);
};

#endif //GLES3JNI_NODE_H
