#include <iostream>
#include <string>

#include "graph.h"
#include "util.h"

const int INT_INF = 2147483647; // equivalent to infinity

// prints the path up to a target
// list - array of vertices and their edges
// t - index of target vertex
void PrintPath(Vertex **list, int t) {
    if(t != -1) { // if t is valid vertex
        PrintPath(list, list[t]->pred); // print predecessor first
        std::cout << t + 1 << ";"; // print self
    }
}

// finds the shortest path from one to another
// flag determines if it returns just the length or the path itself
// list - array of vertices and their edges
// verts - amount of vertices in list
// s - index of starting vertex
// t - index of target vertex
// flag - determines whether to output length or path
void Find(Vertex **list, int verts, int s, int t, int flag) {
    if(s < 0 || s >= verts || t < 0 || t >= verts || (flag != 0 && flag != 1)) { // invalid parameters given
        // invalid nodes
        if (s < 0 || s >= verts || t < 0 || t >= verts) {std::cout << "Error: one or more invalid nodes" << std::endl;}
        // invalid flag
        if (flag != 0 && flag != 1) {std::cout << "Error: invalid flag value" << std::endl;}
    } else {
        // find shortest paths
        Dijkstra(list, verts, s);
        // output
        if(list[t]->dist == INT_INF) {
            // not reachable
            std::cout << "Error: node " << t + 1 << " not reachable from node " << s + 1 << std::endl;
        } else if(flag == 1) {
            // print length
            std::cout << "Length: " << list[t]->dist << std::endl;
        } else if(flag == 0) {
            // print path
            std::cout << "Path: ";
            if(t != -1) {PrintPath(list, list[t]->pred);}
            std::cout << t + 1 << std::endl;
        }
    }
}

// prints out the adjacency list
// list - array of vertices and their edges
// verts - amount of vertices in list
// edges - amount of edges in list
void Write(Vertex **list, int verts, int edges) {
    //print out vertex and edge counts
    std::cout << verts << " " << edges << std::endl;

    // print out each vertex with its edges
    for(int i = 0; i < verts; i++) {
        std::cout << i + 1 << " :";

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
// list - array of vertices and their edges
// verts - amount of vertices in list
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
    int verts = stroi(split(input, ' ', 0, 1));
    int edges = stroi(split(input, ' ', 1, 2));

    // create adjacency list
    Vertex **adjacencyList = new Vertex*[verts];
    InitAdjacencyList(adjacencyList, verts, edges);

    // read in commands
    while(true) {
        // read
        getline(std::cin, input);
        std::string command = split(input, ' ', 0, 1);

        // execute command
        std::cout << "Command: " << input << std::endl;
        if(command == "find") {
            int s = stroi(split(input, ' ', 1, 2));
            int t = stroi(split(input, ' ', 2, 3));
            int flag = stroi(split(input, ' ', 3, 4));
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
