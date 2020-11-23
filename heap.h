#ifndef DIJKSTRAPROJECT_HEAP_H

#include "graph.h"

// min-heap functions
void BuildMinHeap(Vertex **heap, int n);
void Insert(Vertex **heap, Vertex *vertex);
Vertex* Minimum(Vertex **heap);
Vertex* ExtractMin(Vertex **heap);
void DecreaseKey(Vertex **heap, Vertex *vertex, int key);

// dijkstra's algorithm functions
void InitSingleSource(Vertex **list, int verts, int s);
void Relax(Vertex **list, int u, int v, int weight);

#define DIJKSTRAPROJECT_HEAP_H

#endif //DIJKSTRAPROJECT_HEAP_H
