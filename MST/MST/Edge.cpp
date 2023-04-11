#include "Edge.h"

Edge::Edge(Node* node1, Node* node2, int w) {
	n1 = node1;
	n2 = node2;
	weight = w;
	//add the neighbors either here in the Edge constructor
	// or in main (but not both)
	node1->addNeighbor(this);
	node2->addNeighbor(this);
}
