#include <iostream>
#include <string>

#include "graph.h"
#include "heap.h"
#include "util.h"

int main() {
    // input initialization
    std::string input;

    // get vertex and edge count
    getline(std::cin, input);
    int verts = stoi(split(input, ' ', 0, 1));
    int edges = stoi(split(input, ' ', 1, 2));

    // create adjacency list
    Vertex **adjacencyList = new Vertex*[verts];
    initAdjacencyList(adjacencyList, verts, edges);

    return 0;
}
