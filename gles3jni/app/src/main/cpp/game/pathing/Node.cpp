#include <cstdint>
#include <vector>
#include "Node.h"
#include "BinaryHeap.h"

uint64_t currentPathfinderRun = 0;

std::list<Node*> Node::findShortestPath(Node* destination, Agent* agent) {
	currentPathfinderRun++;
	lastVisit = currentPathfinderRun;
	previous = nullptr;

	std::vector<Node*> closed;
	BinaryHeap open;
	open.add(this);

	while (open.count() > 0) {
		auto active = static_cast<Node*>(open.remove());
		active->status = NodeStatus::closed;
		closed.push_back(active);
		if (active == destination) {
			break;
		}

		for (auto& link : getLinks()) {
			auto neighbor = link.getDestination();

			if (neighbor->lastVisit != currentPathfinderRun) {
				neighbor->status = NodeStatus::unvisited;
				neighbor->lastVisit = currentPathfinderRun;
			}

			if (neighbor->status != NodeStatus::closed) {
				auto cost = active->pathCost + link.getCost(agent);

				if (neighbor->status == NodeStatus::unvisited) {
					neighbor->previous = active;
					neighbor->pathCost = cost;
					neighbor->heuristic = neighbor->getHeuristic(destination);
					neighbor->status = NodeStatus::open;
					open.add(neighbor);
				} else if (cost < neighbor->pathCost) {
					neighbor->previous = active;
					neighbor->pathCost = cost;
					open.reposition(neighbor);
				}
			}
		}
	}

	std::list<Node*> path;
	Node* active = destination;
	while (active != nullptr) {
		path.push_front(active);
		active = active->previous;
	}
	return path;
}

int Node::compareTo(Comparable* other) {

}
