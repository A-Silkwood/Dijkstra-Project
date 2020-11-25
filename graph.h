#ifndef DIJKSTRAPROJECT_GRAPH_H

// structs to represent graph
struct Edge; struct Vertex {int id; Edge *edge; int dist; int pred;};
struct Edge {int weight; Vertex *target; Edge *next;};

// graph functions
void InitAdjacencyList(Vertex ** list, int verts, int edges);
void Dijkstra(Vertex **list, int verts, int s);

#define DIJKSTRAPROJECT_GRAPH_H

#endif //DIJKSTRAPROJECT_GRAPH_H
