#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "Edge.h"
#include "Node.h"
#include <map>

using namespace std;

vector<Edge*> bucket;

Edge* getBestEdge() {
    Edge* best = NULL;
    int bestIndex = -1;
    // Keep searching until an unvisited edge is found or the bucket is empty
    while (best == NULL && !bucket.empty()) {
        bestIndex = 0;
        best = bucket[0];
        // Find the edge with the minimum weight in the bucket
        for (int i = 1; i < bucket.size(); i++) {
            Edge* e = bucket[i];
            if (e->weight < best->weight) {
                best = e;
                bestIndex = i;
            }
        }
        // If both nodes of the best edge have already been visited, remove it from the bucket and continue searching
        if (best->n1->visited && best->n2->visited) {
            bucket.erase(bucket.begin() + bestIndex);
            best = NULL;
        }
    }
    return best;
}


void mstPrim(Node* start) {
    vector<Edge*> mstEdges;
    int totalWeight = 0;

    // Add all edges of the starting node to the bucket
    for (Edge* e : start->neighbors) {
        bucket.push_back(e);
    }

    Edge* e = getBestEdge();

    // While there are still edges in the bucket
    while (e != NULL) { 
        Node* node1 = e->n1;
        Node* node2 = e->n2;

        // Mark the first node as visited
        node1->visited = true;

        // Mark the second node as visited
        node2->visited = true;

        // Add the weight of the edge to the total weight of the MST
        totalWeight += e->weight;

        // Add the edge to the MST
        mstEdges.push_back(e);

        // Add all edges of the first node to the bucket
        for (Edge* n1 : node1->neighbors) {
            bucket.push_back(n1);
        }

        // Add all edges of the second node to the bucket
        for (Edge* n2 : node2->neighbors) {
            bucket.push_back(n2);
        }

        // Get the best edge from the bucket
        e = getBestEdge();
    }

    // Print the nodes of the edges in the MST and its total weight
    cout << "MST has a weight of " << totalWeight << " and consists of these edges:\n";
    for (Edge* e : mstEdges) {
        cout << e->n1->label << " - " << e->n2->label << endl;
    }
}




int main(int argc, char** argv)
{
    // Check if command line argument is provided
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0); // Exit the program
    }


    // Debug option for checking file
    //ifstream ifs;
    //ifs.open(argv[1], ios::in);
    //if (!ifs) {
    //    cout << "could not find file " << argv[1] << endl;
    //    exit(0); // Exit the program
    //}


    // Change filename
    string filename = "C:/users/kylem/Desktop/Winter23/mst3.txt";

    // Check if file can be opened for reading
    ifstream ifs;
    ifs.open(filename, ios::in);
    if (!ifs) {
        cout << "File not found" << endl;
        exit(0);
    }

    // Read in the number of nodes and edges
    string nodes, number;
    getline(ifs, nodes);
    getline(ifs, number);
    int lines = stoi(number);

    // Create nodes
    map<char, Node*> nodeMap;
    for (char c : nodes) {
        Node* n = new Node(c);
        nodeMap[c] = n;
    }

    // Create edges
    for (int i = 0; i < lines; i++) {
        string n1, n2;
        int weight;
        ifs >> n1 >> n2 >> weight;
        Edge* e = new Edge(nodeMap[n1[0]], nodeMap[n2[0]], weight);
        nodeMap[n1[0]]->neighbors.push_back(e);
        nodeMap[n2[0]]->neighbors.push_back(e);
    }

    // Set start node and run MST algorithm
    Node* start = nodeMap[nodes[0]];
    mstPrim(start);

    // Close the input file
    ifs.close();

    return 0;
}

