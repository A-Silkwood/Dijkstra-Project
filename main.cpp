#include <iostream>
#include <string>

#include "graph.h"
#include "heap.h"
#include "util.h"

void Find() {
    // space
}

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
            std::cout << "(" << curr->target->id << "; " << curr->weight << std::endl;
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
        if(command == "find") {
            Find(); // find the shortest path
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
