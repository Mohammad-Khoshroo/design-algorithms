#include "topo_dfs.h"

// DFS utility function for topological sort
static void topologicalDFSUtil(Graph* graph, int vertex, int* stack, int* stackIndex) {
    graph->visited[vertex] = true;
    
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;
    
    while (temp) {
        int connectedVertex = temp->vertex;
        
        if (!graph->visited[connectedVertex]) {
            topologicalDFSUtil(graph, connectedVertex, stack, stackIndex);
        }
        temp = temp->next;
    }
    
    stack[*stackIndex] = vertex;
    (*stackIndex)++;
}

// DFS-based topological sort
int* topologicalSortDFS(Graph* graph, int* resultSize) {
    // Reset visited array
    resetVisited(graph);
    
    int* stack = (int*)malloc(graph->numVertices * sizeof(int));
    int stackIndex = 0;
    
    // Call DFS for all vertices
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            topologicalDFSUtil(graph, i, stack, &stackIndex);
        }
    }
    
    // Reverse the stack to get topological order
    int* result = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        result[i] = stack[graph->numVertices - 1 - i];
    }
    
    *resultSize = graph->numVertices;
    free(stack);
    return result;
}

// Cycle detection utility function (for DFS)
static bool hasCycleDFSUtil(Graph* graph, int vertex, bool* recStack) {
    if (!graph->visited[vertex]) {
        graph->visited[vertex] = true;
        recStack[vertex] = true;
        
        Node* temp = graph->adjLists[vertex];
        while (temp) {
            if ((!graph->visited[temp->vertex] && hasCycleDFSUtil(graph, temp->vertex, recStack)) ||
                recStack[temp->vertex]) {
                return true;
            }
            temp = temp->next;
        }
    }
    recStack[vertex] = false;
    return false;
}

// Check if graph has cycle using DFS
bool hasCycleDFS(Graph* graph) {
    bool* recStack = (bool*)calloc(graph->numVertices, sizeof(bool));
    
    // Reset visited array
    resetVisited(graph);
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (hasCycleDFSUtil(graph, i, recStack)) {
            free(recStack);
            return true;
        }
    }
    
    free(recStack);
    return false;
}

// Print topological order
void printTopologicalOrder(int* order, int size) {
    if (order == NULL || size == 0) {
        printf("No valid topological order (graph has cycle)\n");
        return;
    }
    
    printf("Topological Order: ");
    for (int i = 0; i < size; i++) {
        printf("%d", order[i]);
        if (i < size - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}
