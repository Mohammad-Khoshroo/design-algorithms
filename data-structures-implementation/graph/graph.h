#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph structure using adjacency list
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
    int* indegree;
} Graph;

// Function prototypes
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void destroyGraph(Graph* graph);
void resetVisited(Graph* graph);
bool isEmptyGraph(Graph* graph);

#endif
