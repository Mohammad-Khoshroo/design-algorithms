#ifndef TOPO_KAHN_H
#define TOPO_KAHN_H

#include "graph.h"
#include "queue.h"

// Function prototypes for Kahn's algorithm
int* topologicalSortKahn(Graph* graph, int* resultSize);
bool hasCycleKahn(Graph* graph);

#endif
