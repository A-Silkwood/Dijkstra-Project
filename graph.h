#ifndef DIJKSTRAPROJECT_GRAPH_H

struct Edge {
    int value;
    Edge *next;
};

struct Vertex {
    int key;
    Edge *edge;
};

#define DIJKSTRAPROJECT_GRAPH_H

#endif //DIJKSTRAPROJECT_GRAPH_H
