#include "topo_kahn.h"

// Kahn's algorithm (BFS-based) topological sort
int* topologicalSortKahn(Graph* graph, int* resultSize) {
    Queue* queue = createQueue();
    int* result = (int*)malloc(graph->numVertices * sizeof(int));
    int index = 0;
    
    // Initialize queue with all vertices having indegree 0
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->indegree[i] == 0) {
            enqueue(queue, i);
        }
    }
    
    // Process vertices in queue
    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        result[index++] = currentVertex;
        
        // Reduce indegree of adjacent vertices
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            graph->indegree[adjVertex]--;
            
            // If indegree becomes 0, add to queue
            if (graph->indegree[adjVertex] == 0) {
                enqueue(queue, adjVertex);
            }
            
            temp = temp->next;
        }
    }
    
    destroyQueue(queue);
    
    // Check if all vertices were processed (no cycle)
    if (index != graph->numVertices) {
        // Graph has cycle
        free(result);
        *resultSize = 0;
        return NULL;
    }
    
    *resultSize = graph->numVertices;
    return result;
}

// Check if graph has cycle using Kahn's algorithm
bool hasCycleKahn(Graph* graph) {
    // Create a copy of indegrees since Kahn's algorithm modifies them
    int* tempIndegree = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        tempIndegree[i] = graph->indegree[i];
    }
    
    Queue* queue = createQueue();
    int processedCount = 0;
    
    // Initialize queue with all vertices having indegree 0
    for (int i = 0; i < graph->numVertices; i++) {
        if (tempIndegree[i] == 0) {
            enqueue(queue, i);
        }
    }
    
    // Process vertices in queue
    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        processedCount++;
        
        // Reduce indegree of adjacent vertices
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            tempIndegree[adjVertex]--;
            
            // If indegree becomes 0, add to queue
            if (tempIndegree[adjVertex] == 0) {
                enqueue(queue, adjVertex);
            }
            
            temp = temp->next;
        }
    }
    
    destroyQueue(queue);
    free(tempIndegree);
    
    // If not all vertices were processed, there's a cycle
    return processedCount != graph->numVertices;
}
