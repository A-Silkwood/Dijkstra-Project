#include <iostream>
#include "graph.h"

// return position of the parent in a min-heap
int Parent(int i) {
    return (i - 1) / 2;
}

// return position of the left child in a min-heap
int Left(int i) {
    return 2 * i + 1;
}

// return position of the right child in a min-heap
int Right(int i) {
    return 2 * i + 2;
}

// maintain the min-heap property at given position
// assumes its left and right subtrees are min-heaps
void MinHeapify(Vertex **heap, int i, int n) {
    // get positions of left and right children
    int l = Left(i);
    int r = Right(i);

    // find the smallest key between a parent and its left and right child
    int smallest = i;
    if(l <= n && heap[l]->key < heap[smallest]->key) {smallest = l;}
    if(r <= n && heap[r]->key < heap[smallest]->key) {smallest = r;}

    // correct min-heap if the parent does not have the smallest key
    if(smallest != i) {
        // swap parent with smallest child
        Vertex *temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        // check subtree affected for maintenance
        MinHeapify(heap, smallest, n);
    }
}

// create a min-heap from an array of Vertex pointers
void BuildMinHeap(Vertex **heap, int n) {
    for(int i = n / 2; i >= 0; i--) {MinHeapify(heap, i, n);}
}

// inserts a vertex into the min-heap
void Insert(Vertex **heap, Vertex *vertex) {
    // stop at first null pointer in min-heap
    int ix = 0;
    while(heap[ix] != NULL) {ix++;} // assumes 1 null pointer at the end of the heap
    // add vertex at first null pointer
    heap[ix] = vertex;

    // rebuild min-heap
    BuildMinHeap(heap, ix + 1);
}

// returns the vertex with the smallest key
Vertex* Minimum(Vertex **heap) {
    return heap[0];
}

// returns and removes the vertex with the smallest key
Vertex* ExtractMin(Vertex **heap) {
    Vertex *min = heap[0]; // save min vertex

    // stop at first null pointer in min-heap
    int n = 0;
    while(heap[n] != NULL) {n++;} // assumes 1 null pointer at the end of the heap
    // move last leaf to root of min-heap
    heap[0] = heap[n - 1];

    // check and maintain min-heap property
    MinHeapify(heap, 0, n);

    return min; // return min vertex
}

// changes the key of a vertex to a value less than or equal to its current key
void DecreaseKey(Vertex **heap, Vertex *vertex, int key) {
    // check if key is less than
    if(key < vertex->key) {
        vertex->key = key; // change key

        // find array length
        int n = 0;
        while(heap[n] != NULL) {n++;} // assumes 1 null pointer at the end of the heap

        // rebuild min-heap
        BuildMinHeap(heap, n);
    }
}
