#include "graph.h"

// Create a new node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));
    graph->indegree = (int*)calloc(vertices, sizeof(int));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    
    return graph;
}

// Add edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // Increment indegree of destination
    graph->indegree[dest]++;
}

// Free memory allocated for the graph
void destroyGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph->indegree);
    free(graph);
}

// Reset visited array
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = false;
    }
}

// Check if graph is empty
bool isEmptyGraph(Graph* graph) {
    return graph->numVertices == 0;
}
