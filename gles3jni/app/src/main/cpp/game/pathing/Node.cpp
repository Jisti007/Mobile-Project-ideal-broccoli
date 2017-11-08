#include "Node.h"
#include "BinaryHeap.h"

uint64_t currentPathfinderRun = 0;

Node::Node() {

}

Node::~Node() {

}

std::list<Link*> Node::findShortestPath(Node* destination, Agent* agent, size_t graphSize) {
	currentPathfinderRun++;
	this->lastVisit = currentPathfinderRun;
	this->pathLink = nullptr;

	BinaryHeap open;
	open.reserve(graphSize);
	open.add(this);

	while (open.count() > 0) {
		auto active = static_cast<Node*>(open.remove());
		active->status = NodeStatus::closed;
		if (active == destination) {
			break;
		}

		for (auto& link : active->links) {
			auto neighbor = link->getDestination();

			if (neighbor->lastVisit != currentPathfinderRun) {
				neighbor->status = NodeStatus::unvisited;
				neighbor->lastVisit = currentPathfinderRun;
			}

			if (neighbor->status != NodeStatus::closed) {
				auto cost = active->pathCost + link->getCost(agent, active->pathCost);

				if (neighbor->status == NodeStatus::unvisited) {
					neighbor->pathLink = link.get();// active;
					neighbor->pathCost = cost;
					neighbor->heuristic = neighbor->getHeuristic(destination);
					neighbor->status = NodeStatus::open;
					open.add(neighbor);
				} else if (cost < neighbor->pathCost) {
					neighbor->pathLink = link.get();//active;
					neighbor->pathCost = cost;
					open.reposition(neighbor);
				}
			}
		}
	}

	// Backtrack from the destination to build the path.
	std::list<Link*> path;
	Link* pathLink = destination->pathLink;
	while (pathLink != nullptr) {
		path.push_front(pathLink);
		pathLink = pathLink->getSource()->pathLink;
	}
	return path;
}

int Node::compareTo(Comparable* other) {
	auto valueSelf = pathCost + heuristic;
	auto otherNode = (Node*)other;
	auto valueOther = otherNode->pathCost + otherNode->heuristic;
	if (valueSelf > valueOther) {
		return 1;
	}
	if (valueSelf < valueOther) {
		return -1;
	}
	return 0;
}
