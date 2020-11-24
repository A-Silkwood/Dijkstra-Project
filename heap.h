#ifndef DIJKSTRAPROJECT_HEAP_H

#include "graph.h"

void BuildMinHeap(Vertex **heap, int n);
void Insert(Vertex **heap, Vertex *vertex);
Vertex* Minimum(Vertex **heap);
Vertex* ExtractMin(Vertex **heap, int size);
void DecreaseKey(Vertex **heap, int size, Vertex *vertex, int key);

#define DIJKSTRAPROJECT_HEAP_H

#endif //DIJKSTRAPROJECT_HEAP_H
