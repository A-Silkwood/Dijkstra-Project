#include <iostream>

#include "graph.h"
#include "util.h"

const int INT_INF = 2147483647;

void initAdjacencyList(Vertex ** list, int verts, int edges) {
    // add vertices to list
    for (int i = 0; i < verts; i++) {
        list[i] = new Vertex;
        list[i]->id = i + 1;
        list[i]->key = INT_INF;
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
        edge->next = NULL;
        edge->target = list[v];
        edge->weight = w;

        // find edge location in list and place it
        Edge *curr = list[u]->edge;
        if (curr == NULL) {
            list[u]->edge = edge;
        } else {
            while (curr->next != NULL) { curr = curr->next; }
            curr->next = edge;
        }
    }
}

void showList(Vertex **list, int verts) {
    for (int i = 0; i < verts; i++) {
        std::cout << "Vertex [" << list[i]->id << "] -" << std::endl;
        Edge *edge = list[i]->edge;
        while (edge != NULL) {
            std::cout << "\tID:" << edge->target->id << ", Weight:" << edge->weight << std::endl;
            edge = edge->next;
        }
    }
}
