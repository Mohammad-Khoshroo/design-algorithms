#include <stdio.h>
#include "DFS/topo-sort.h"
#include "Kahn/topo-sort.h"

int main() {
    printf("=== Topological Sorting Examples ===\n\n");
    
    // Create a graph with 6 vertices
    Graph* graph = createGraph(6);
    
    // Add edges (representing dependencies)
    // 5 -> 2, 5 -> 0, 4 -> 0, 4 -> 1, 2 -> 3, 3 -> 1
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);
    
    // Check for cycle using both methods
    if (hasCycleDFS(graph)) {
        printf("Graph contains cycle (detected by DFS). Topological sort not possible.\n");
    } else if (hasCycleKahn(graph)) {
        printf("Graph contains cycle (detected by Kahn's algorithm). Topological sort not possible.\n");
    } else {
        printf("Graph is acyclic (DAG). Proceeding with topological sort.\n\n");
        
        // Using DFS approach
        printf("1. DFS-based Topological Sort:\n");
        int dfsSize;
        int* dfsResult = topologicalSortDFS(graph, &dfsSize);
        printTopologicalOrder(dfsResult, dfsSize);
        free(dfsResult);
        
        printf("\n");
        
        // Using Kahn's algorithm
        printf("2. Kahn's Algorithm (BFS-based):\n");
        int kahnSize;
        int* kahnResult = topologicalSortKahn(graph, &kahnSize);
        printTopologicalOrder(kahnResult, kahnSize);
        free(kahnResult);
    }
    
    printf("\n=== Course Prerequisites Example ===\n");
    
    // Create a new graph for course prerequisites
    Graph* courseGraph = createGraph(5);
    
    // Course dependencies:
    // 0 -> 1 (Course 0 is prerequisite for Course 1)
    // 0 -> 2 (Course 0 is prerequisite for Course 2)
    // 1 -> 3 (Course 1 is prerequisite for Course 3)
    // 2 -> 3 (Course 2 is prerequisite for Course 3)
    // 3 -> 4 (Course 3 is prerequisite for Course 4)
    addEdge(courseGraph, 0, 1);
    addEdge(courseGraph, 0, 2);
    addEdge(courseGraph, 1, 3);
    addEdge(courseGraph, 2, 3);
    addEdge(courseGraph, 3, 4);
    
    if (!hasCycleKahn(courseGraph)) {
        printf("Course schedule can be arranged as follows:\n");
        int courseSize;
        int* courseOrder = topologicalSortKahn(courseGraph, &courseSize);
        printf("Take courses in this order: ");
        for (int i = 0; i < courseSize; i++) {
            printf("Course %d", courseOrder[i]);
            if (i < courseSize - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
        free(courseOrder);
    }
    
    // Clean up
    destroyGraph(graph);
    destroyGraph(courseGraph);
    
    return 0;
}
