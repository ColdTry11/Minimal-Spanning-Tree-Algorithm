#pragma once

#include "Node.h"

class Edge
{
public:
	Node* n1;
	Node* n2;
	int weight;
	Edge(Node*, Node*, int);
};

