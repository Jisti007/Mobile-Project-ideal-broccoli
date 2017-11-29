#include "Path.h"

Path::Path(std::list<Link*> links, Agent* agent) {
	this->links = links;
	for (auto& link : links) {
		cost += link->getCost(agent, cost);
	}
}
