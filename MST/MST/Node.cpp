#include "Node.h"

Node::Node(char lab) {
	label = lab;
	visited = false;
}

void Node::addNeighbor(Edge* marley) {
	neighbors.push_back(marley);
}