#include "Path.h"

Path::Path() {

}

Path::Path(std::list<Link*> links, Agent* agent) {
	this->links = links;
	for (auto& link : links) {
		cost += link->getCost(agent, cost);
	}
}

void Path::popLast() {
	auto link = links.back();
	cost -= link->getCost(agent, cost);
	links.pop_back();
}

/*
void Path::shorten(float maxCost) {
	while (cost > maxCost) {
		auto link = links.back();
		cost -= link->getCost(agent, cost);
		links.pop_back();
	}
}
*/
