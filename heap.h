#ifndef DIJKSTRAPROJECT_HEAP_H

#include "graph.h"

void Insert(Vertex **heap, Vertex *vertex);
Vertex* Minimum(Vertex **heap);
Vertex* ExtractMin(Vertex **heap);
void DecreaseKey(Vertex **heap, Vertex *vertex, int key);

#define DIJKSTRAPROJECT_HEAP_H

#endif //DIJKSTRAPROJECT_HEAP_H
