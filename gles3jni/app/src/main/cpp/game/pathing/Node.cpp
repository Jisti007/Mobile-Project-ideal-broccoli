#include "Node.h"

uint64_t currentPathfinderRun = 0;

Node::Node() {

}

Node::~Node() {

}

Path Node::findShortestPath(Node* destination, Agent* agent, size_t graphSize) {
	BinaryHeap openNodes;
	initializePathfinder(openNodes, graphSize);

	while (openNodes.count() > 0) {
		auto active = static_cast<Node*>(openNodes.remove());
		active->status = NodeStatus::closed;
		if (active == destination) {
			break;
		}

		active->visitNeighbors(openNodes, agent, destination);
	}

	return buildPath(destination, agent);
}

std::vector<Node*> Node::findAllNodes(Agent* agent, float maxPathCost, size_t graphSize) {
	std::vector<Node*> nodesFound;
	BinaryHeap openNodes;
	initializePathfinder(openNodes, graphSize);

	while (openNodes.count() > 0) {
		auto active = static_cast<Node*>(openNodes.remove());
		active->status = NodeStatus::closed;
		if (active->pathCost > maxPathCost) {
			break;
		}

		nodesFound.push_back(active);
		active->visitNeighbors(openNodes, agent);
	}

	return nodesFound;
}

Path Node::buildPath(Node* destination, Agent* agent) {
	std::list<Link*> links;
	if (destination->lastVisit == currentPathfinderRun) {
		// Backtrack from the destination to build the path.
		Link* pathLink = destination->pathLink;
		while (pathLink != nullptr) {
			links.push_front(pathLink);
			pathLink = pathLink->getSource()->pathLink;
		}
	}
	return Path(links, agent);
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

void Node::initializePathfinder(BinaryHeap& openNodes, size_t graphSize) {
	currentPathfinderRun++;
	this->lastVisit = currentPathfinderRun;
	this->pathLink = nullptr;
	openNodes.reserve(graphSize);
	openNodes.add(this);
}

void Node::visitNeighbors(BinaryHeap& openNodes, Agent* agent) {
	for (auto& link : links) {
		auto neighbor = link->getDestination();
		neighbor->tryReset();

		switch (neighbor->status) {
			case NodeStatus::unvisited:
				neighbor->heuristic = 0;
				neighbor->tryOpen(openNodes, link.get(), agent);
				break;
			case NodeStatus::open:
				neighbor->tryReposition(openNodes, link.get(), agent);
				break;
			case NodeStatus::closed:
				break;
		}
	}
}

void Node::visitNeighbors(BinaryHeap& openNodes, Agent* agent, Node* destination) {
	for (auto& link : links) {
		auto neighbor = link->getDestination();
		neighbor->tryReset();

		switch (neighbor->status) {
			case NodeStatus::unvisited:
				neighbor->heuristic = neighbor->getHeuristic(destination);
				neighbor->tryOpen(openNodes, link.get(), agent);
				break;
			case NodeStatus::open:
				neighbor->tryReposition(openNodes, link.get(), agent);
				break;
			case NodeStatus::closed:
				break;
		}
	}
}

void Node::tryReset() {
	if (lastVisit != currentPathfinderRun) {
		status = NodeStatus::unvisited;
		lastVisit = currentPathfinderRun;
	}
}

void Node::tryOpen(BinaryHeap& openNodes, Link* link, Agent* agent) {
	auto source = link->getSource();
	auto cost = source->pathCost + link->getCost(agent, source->pathCost);
	pathLink = link;
	pathCost = cost;
	status = NodeStatus::open;
	openNodes.add(this);
}

void Node::tryReposition(BinaryHeap& openNodes, Link* link, Agent* agent) {
	auto source = link->getSource();
	auto cost = source->pathCost + link->getCost(agent, source->pathCost);
	if (cost < pathCost) {
		pathLink = link;
		pathCost = cost;
		openNodes.reposition(this);
	}
}
