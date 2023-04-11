#pragma once

#include <string>
#include <vector>

using namespace std;

class Edge;

class Node
{
public:
	char label;
	bool visited;
	vector<Edge*> neighbors;
	Node(char);
	void addNeighbor(Edge*);
};

