#ifndef DIJKSTRAPROJECT_GRAPH_H

struct Edge; struct Vertex {int id; Edge *edge; int dist; int pred;};
struct Edge {int weight; Vertex *target; Edge *next;};

void initAdjacencyList(Vertex ** list, int verts, int edges);

#define DIJKSTRAPROJECT_GRAPH_H

#endif //DIJKSTRAPROJECT_GRAPH_H
