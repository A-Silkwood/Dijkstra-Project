#ifndef DIJKSTRAPROJECT_GRAPH_H

struct Edge; struct Vertex {int id; int key; Edge *edge;};
struct Edge {int weight; Vertex *target; Edge *next;};

void initAdjacencyList(Vertex ** list, int verts, int edges);
void showList(Vertex **list, int verts);

#define DIJKSTRAPROJECT_GRAPH_H

#endif //DIJKSTRAPROJECT_GRAPH_H
