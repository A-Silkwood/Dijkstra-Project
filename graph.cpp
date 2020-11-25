#include <iostream>

#include "heap.h"
#include "util.h"

const int INT_INF = 2147483647; // equivalent to infinity

// initializes an adjacency list from input of given edges
// list - initialized array for vertices
// verts - amount of vertices in graph
// edges - amount of edges to read in
void InitAdjacencyList(Vertex ** list, int verts, int edges) {
    // add vertices to list
    for (int i = 0; i < verts; i++) {
        list[i] = new Vertex;
        list[i]->id = i + 1;
        list[i]->edge = NULL;
    }

    std::string input;
    // add edges to vertices
    for (int i = 0; i < edges; i++) {
        // read in line
        getline(std::cin, input);
        int u = stroi(split(input, ' ', 0, 1)) - 1; // vertex index
        int v = stroi(split(input, ' ', 1, 2)) - 1; // target vertex index
        int w = stroi(split(input, ' ', 2, 3)); // weight of edge

        // initialize edge
        Edge *edge = new Edge;
        edge->target = list[v];
        edge->weight = w;

        // insert edge
        edge->next = list[u]->edge;
        list[u]->edge = edge;
    }
}

// initializes each vertex for single source shortest path algorithm
// list - adjacency list of vertices and their edges
// verts - vertices in list
// s - starting vertex index
void InitSingleSource(Vertex **list, int verts, int s) {
    for(int i = 0; i < verts; i++) {
        list[i]->dist = INT_INF; // not reachable
        list[i]->pred = -1; // no predecessor
    }
    list[s]->dist = 0; // start has 0 distance
}

// relaxes path to the shorter of the two given
// list - adjacency list of vertices and their edges
// u - vertex index with possible new path
// v - vertex index to relax the path for
// weight - weight of the edge from u to v
void Relax(Vertex **list, int u, int v, int weight) {
    // check if new path is shorter
    if(list[v]->dist > list[u]->dist + weight) {
        list[v]->dist = list[u]->dist + weight;
        list[v]->pred = u;
    }
}

// Dijkstra's Single Source Shortest Path Algorithm
// list - adjacency list of vertices and their edges
// verts - amount of vertices in the adjacency list
// s - index of the starting vertex
void Dijkstra(Vertex **list, int verts, int s) {
    // initialize vertices to default values
    InitSingleSource(list, verts, s);

    // create set of used vertices
    Vertex **S = new Vertex*[verts];
    int sizeS = 0;
    // create min-heap
    Vertex **Q = new Vertex*[verts];
    int sizeQ = verts;
    // initialize set and min-heap
    for(int i = 0; i < verts; i++) {
        S[i] = NULL;
        Q[i] = list[i];
    }
    // build min-heap; put starting vertex to root of heap
    BuildMinHeap(Q, sizeQ);

    // find shortest paths
    while(sizeQ != 0 && Minimum(Q)->dist != INT_INF) {
        // add next min to set
        Vertex *u = ExtractMin(Q, sizeQ--);
        S[sizeS++] = u;
        // relax all adjacent vertices paths from u
        Edge *curr = u->edge;
        while(curr != NULL) {
            // check if vertex is in set
            bool inSet = false;
            for(int i = 0; i < sizeS; i++) {
                if(curr->target->id == S[i]->id) {
                    inSet = true;
                    break;
                }
            }
            // relax path if not in set
            if(!inSet) {Relax(list, u->id - 1, curr->target->id - 1, curr->weight);}
            // check next edge
            curr = curr->next;
        }
        // rebuild heap after relaxing distances
        BuildMinHeap(Q, sizeQ);
    }

    // deallocate memory used
    delete S;
    delete Q;
}
