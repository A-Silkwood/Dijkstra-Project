#include <iostream>

#include "heap.h"
#include "util.h"

const int INT_INF = 2147483647;

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
void InitSingleSource(Vertex **list, int verts, int s) {
    for(int i = 0; i < verts; i++) {
        list[i]->dist = INT_INF; // not reachable
        list[i]->pred = -1; // no predecessor
    }
    list[s]->dist = 0; // start has 0 distance
}

// relaxes path to the shorter of the two given
void Relax(Vertex **list, int u, int v, int weight) {
    // check if new path is shorter
    if(list[v]->dist > list[u]->dist + weight) {
        list[v]->dist = list[u]->dist + weight;
        list[v]->pred = u;
    }
}

// Dijkstra's Single Source Shortest Path Algorithm
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
    BuildMinHeap(Q, sizeQ);

    // find shortest paths
    while(sizeQ != 0) {
        Vertex *u = ExtractMin(Q, sizeQ--);
        S[sizeS++] = u;
        // relax all adjacent vertices path
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

            if(!inSet) {Relax(list, u->id - 1, curr->target->id - 1, curr->weight);}
            curr = curr->next;
        }
        // rebuild heap after relaxing distances
        BuildMinHeap(Q, sizeQ);
    }

    // deallocate memory used
    delete S;
    delete Q;
}
