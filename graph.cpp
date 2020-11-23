#include <iostream>

#include "graph.h"
#include "util.h"

void initAdjacencyList(Vertex ** list, int verts, int edges) {
    // add vertices to list
    for (int i = 0; i < verts; i++) {
        list[i] = new Vertex;
        list[i]->id = i + 1;
        list[i]->edge = NULL;
    }

    std::string input;
    // add edges to vertices
    for (int i = 0; i < edges; i++) {
        // read in line
        getline(std::cin, input);
        int u = stoi(split(input, ' ', 0, 1)) - 1; // vertex index
        int v = stoi(split(input, ' ', 1, 2)) - 1; // target vertex index
        int w = stoi(split(input, ' ', 2, 3)); // weight of edge

        // initialize edge
        Edge *edge = new Edge;
        edge->target = list[v];
        edge->weight = w;

        // insert edge
        edge->next = list[u]->edge;
        list[u]->edge = edge;
    }
}
