#include <iostream>
#include <string>

#include "graph.h"
#include "heap.h"
#include "util.h"

const int INT_INF = 2147483647;

void PrintPath(Vertex **list, int t) {
    PrintPath(list, list[t]->pred);
    std::cout << t << ";";
}

// finds the shortest path from one to another
// flag determines if it returns just the length or the path itself
void Find(Vertex **list, int verts, int s, int t, int flag) {
    if(s < 0 || s >= verts || t < 0 || t >= verts || (flag != 0 && flag != 1)) {
        // invalid parameters
        if (s < 0 || s >= verts || t < 0 || t >= verts) {std::cout << "Error: one or more invalid nodes" << std::endl;}
        if (flag != 0 && flag != 1) {std::cout << "Error: invalid flag value" << std::endl;}
    } else { // Dijkstra's Single Source Shortest Path Algorithm
        InitSingleSource(list, verts, s);
        Vertex **set = new Vertex*[verts];
        Vertex **heap = new Vertex*[verts+1];
        // insert all vertices into heap
        for(int i = 0; i < verts; i++) {
            heap[i] = list[i];
        }
        heap[verts] = NULL; // used to find end of heap
        BuildMinHeap(heap, verts);

        int i = 0;
        while(heap[0] != NULL /* at least 1 vertex in heap */) {
           Vertex *u = ExtractMin(heap);
           set[i++] = u;
           Edge *curr = u->edge;
           while(curr != NULL) {
               Relax(list, u->id-1, curr->target->id-1, curr->weight);
               curr = curr->next;
           }
        }

        // output
        if(list[t]->dist == INT_INF) {
            // node was not reachable
            std::cout << "Error: node " << t + 1 << "not reachable from node " << s + 1 << std::endl;
        } else if(flag == 0) {
            // flag zero just outputs length
            std::cout << "Length: " << list[t]->dist << std::endl;
        } else if(flag == 1) {
            // flag one outputs shortest path found
            std::cout << "Path: ";
            PrintPath(list, list[t]->pred);
            std::cout << t << std::endl;
        }

        // deallocate heap
        for(int i = 0; i < verts+1; i++) {
            if(heap[i] != NULL) {delete heap[i];}
        }
        delete heap;
    }
}

// prints out the adjacency list
void Write(Vertex **list, int verts, int edges) {
    //print out vertex and edge counts
    std::cout << verts << " " << edges << std::endl;

    // print out each vertex with its edges
    for(int i = 0; i < verts; i++) {
        std::cout << i << " :";

        Edge *curr = list[i]->edge;
        if (curr != NULL) {
            std::cout << " ";
            // print out each edge
            while (curr->next != NULL) {
                std::cout << "(" << curr->target->id << "; " << curr->weight << "); ";
                curr = curr->next;
            }
            std::cout << "(" << curr->target->id << "; " << curr->weight << ")" << std::endl;
        }
    }
}

// deallocates all memory in a adjacency list
void DeallocateMem(Vertex **list, int verts) {
    // delete all vertices and edges
    for(int i = 0; i < verts; i++) {
        Edge *curr = list[i]->edge;
        Edge *next = NULL;
        if (curr != NULL) {
            // delete all edges
            while (curr->next != NULL) {
                next = curr->next;
                delete curr;
                curr = next;
            }
            delete curr;
        }
        // delete vertex
        delete list[i];
    }
}

int main() {
    // input initialization
    std::string input;

    // get vertex and edge count
    getline(std::cin, input);
    int verts = stoi(split(input, ' ', 0, 1));
    int edges = stoi(split(input, ' ', 1, 2));

    // create adjacency list
    Vertex **adjacencyList = new Vertex*[verts];
    initAdjacencyList(adjacencyList, verts, edges);

    // read in commands
    while(true) {
        // read
        getline(std::cin, input);
        std::string command = split(input, ' ', 0, 1);

        // execute command
        std::cout << "Command: " << input << std::endl;
        if(command == "find") {
            int s = stoi(split(input, ' ', 1, 2));
            int t = stoi(split(input, ' ', 2, 3));;
            int flag = stoi(split(input, ' ', 3, 4));;
            Find(adjacencyList, verts, s - 1, t - 1, flag); // find the shortest path
        } else if(command == "write") {
            Write(adjacencyList, verts, edges); // write the graph to output
        } else if(command == "stop") {
            // deallocate memory
            DeallocateMem(adjacencyList, verts);
            delete [] adjacencyList;
            break; // exit loop
        } else {
            // error reading line
            std::cout << "INPUT: " << input << std::endl;
            std::cout << "COMMAND: " << command << std::endl;
        }
    }

    return 0;
}
