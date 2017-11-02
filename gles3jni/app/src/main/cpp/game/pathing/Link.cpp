#include "Link.h"

Link::Link(Node* source, Node* destination) {
	this->source = source;
	this->destination = destination;
}

Link::~Link() {

}

SimpleLink::SimpleLink(Node* source, Node* destination, float cost)
	: Link(source, destination) {
	this->cost = cost;
}

SimpleLink::~SimpleLink() {

}
