#ifndef TOPO_DFS_H
#define TOPO_DFS_H

#include "graph.h"

// Function prototypes for DFS-based topological sort
int* topologicalSortDFS(Graph* graph, int* resultSize);
bool hasCycleDFS(Graph* graph);
void printTopologicalOrder(int* order, int size);

#endif
