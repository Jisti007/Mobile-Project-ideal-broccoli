#ifndef GLES3JNI_NODE_H
#define GLES3JNI_NODE_H

class Link;
class Path;

#include "Comparable.h"
#include "Agent.h"
#include "Link.h"
#include "BinaryHeap.h"
#include "Path.h"
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
	Path findShortestPath(Node* destination, Agent* agent, size_t graphSize = 128);

	Path findNearest(Agent* agent, std::function<bool(Node*)> condition, size_t graphSize = 128);

	/// \param graphSize The estimated number of nodes traversed.
	std::vector<Node*> findAllNodes(Agent* agent, float maxPathCost, size_t graphSize = 128);

	/// Should only be called after pathfinding has finished and before it is called again.
	/// findShortestPath uses this function automatically,  but it can be useful after findAllNodes.
	/// Returns an empty path if the node wasn't visited in the preceding pathfinding run.
	Path buildPath(Node* destination, Agent* agent);

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
