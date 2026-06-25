# Directed Graph Data Structure

A comprehensive guide to directed graphs including theory, implementation, and practical examples.

## Table of Contents
1. [Introduction](#introduction)
2. [Basic Concepts](#basic-concepts)
3. [Graph Representations](#graph-representations)
4. [Implementation in C](#implementation-in-c)
5. [Implementation in C++](#implementation-in-cpp)
6. [Implementation in Python](#implementation-in-python)
7. [Applications](#applications)
8. [Time Complexities](#time-complexities)

## Introduction

A **directed graph** (or digraph) is a set of objects (called vertices or nodes) connected by directed edges. Unlike undirected graphs where edges have no direction, in directed graphs each edge points from one vertex to another.

Directed graphs are essential in modeling relationships where direction matters:
- Web page links
- Social media followings
- Task dependencies
- Flow networks


## Basic Concepts

### Vertices and Edges
- **Vertex (Node)**: Fundamental unit of the graph
- **Edge (Arc)**: Connection between two vertices with a specific direction
- **Adjacent Vertices**: Two vertices connected by an edge

### Types of Edges in Directed Graphs
1. **Tree Edge**: Edge that discovers a new vertex in DFS traversal
2. **Back Edge**: Edge pointing from a vertex to an ancestor in DFS tree (indicates cycle)
3. **Forward Edge**: Edge pointing from a vertex to a descendant in DFS tree
4. **Cross Edge**: All other edges

### Important Properties
- **In-degree**: Number of edges coming into a vertex
- **Out-degree**: Number of edges going out from a vertex
- **Path**: Sequence of vertices connected by edges following their direction
- **Cycle**: Path that starts and ends at the same vertex

### Directed Acyclic Graph (DAG)
A directed graph without cycles is called a **DAG**. DAGs are fundamental for:
- Topological sorting
- Dynamic programming
- Dependency resolution

## Graph Representations

### 1. Adjacency Matrix
A 2D array where cell `[i][j]` represents edge from vertex `i` to `j`.

**Pros**:
- Fast edge lookup: O(1)
- Simple to implement

**Cons**:
- Space inefficient: O(V²)
- Slow iteration over neighbors

### 2. Adjacency List
Array of lists where each list contains neighbors of a vertex.

**Pros**:
- Space efficient: O(V + E)
- Fast iteration over neighbors
- Good for sparse graphs

**Cons**:
- Slower edge lookup: O(degree)


The adjacency list representation is generally preferred due to its space efficiency and performance characteristics for most real-world applications. Understanding both theoretical concepts and practical implementations enables effective problem-solving across many domains including computer science, mathematics, and engineering.

## Implementation in C

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph structure
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
    int* indegree;
} Graph;

// Create a new node
Node* createNode(int vertex) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Create graph with specified vertices
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(bool));
    graph->indegree = calloc(vertices, sizeof(int));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    
    return graph;
}

// Add directed edge from src to dest
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // Increment indegree of destination
    graph->indegree[dest]++;
}

// Print graph representation
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        printf("Vertex %d: ", v);
        Node* temp = graph->adjLists[v];
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Free memory
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

// Example usage
int main() {
    Graph* graph = createGraph(5);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 1, 4);
    
    printGraph(graph);
    destroyGraph(graph);
    
    return 0;
}
```

## Implementation in C++

```cpp
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
private:
    int numVertices;
    vector<list<int>> adjLists;
    vector<bool> visited;
    vector<int> indegree;

public:
    // Constructor
    Graph(int vertices) {
        numVertices = vertices;
        adjLists.resize(vertices);
        visited.resize(vertices, false);
        indegree.resize(vertices, 0);
    }
    
    // Add directed edge
    void addEdge(int src, int dest) {
        adjLists[src].push_front(dest);
        indegree[dest]++;
    }
    
    // Print graph
    void printGraph() {
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjLists[i]) {
                cout << neighbor << " -> ";
            }
            cout << "NULL" << endl;
        }
    }
    
    // Getters
    const vector<list<int>>& getAdjLists() const { return adjLists; }
    const vector<int>& getIndegree() const { return indegree; }
    int getNumVertices() const { return numVertices; }
};

// Example usage
int main() {
    Graph graph(5);
    
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(1, 4);
    
    graph.printGraph();
    
    return 0;
}
```

## Implementation in Python

```python
from collections import defaultdict, deque

class Graph:
    def __init__(self, vertices):
        self.num_vertices = vertices
        self.adj_lists = defaultdict(list)
        self.indegree = [0] * vertices
        self.visited = [False] * vertices
    
    def add_edge(self, src, dest):
        """Add directed edge from src to dest"""
        self.adj_lists[src].append(dest)
        self.indegree[dest] += 1
    
    def print_graph(self):
        """Print adjacency list representation"""
        for i in range(self.num_vertices):
            neighbors = ' -> '.join(map(str, self.adj_lists[i])) if self.adj_lists[i] else ''
            print(f"Vertex {i}: {neighbors}{' -> NULL' if neighbors else 'NULL'}")
    
    def get_neighbors(self, vertex):
        """Get all neighbors of a vertex"""
        return self.adj_lists[vertex]
    
    def reset_visited(self):
        """Reset visited flags"""
        self.visited = [False] * self.num_vertices

# Example usage
if __name__ == "__main__":
    # Create graph with 5 vertices
    g = Graph(5)
    
    # Add edges
    g.add_edge(0, 1)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(3, 4)
    g.add_edge(1, 4)
    
    # Print graph
    g.print_graph()
    
    # Access properties
    print(f"\nNumber of vertices: {g.num_vertices}")
    print(f"In-degrees: {g.indegree}")
```

## Applications

### 1. Dependency Resolution
Directed graphs naturally represent dependencies:
- Software package management (pip, npm)
- Build systems (Make, Gradle)
- Course prerequisites

### 2. Network Modeling
- Web page linking structure
- Social media follow relationships
- Communication networks

### 3. Scheduling Problems
- Task scheduling with precedence constraints
- Project management (PERT/CPM)
- Instruction scheduling in compilers

### 4. State Machines
- Finite automata in compilers
- Game states
- Workflow systems

### 5. Recommendation Systems
- User-item preference graphs
- Content recommendation flows

## Time Complexities

### Adjacency List Representation
| Operation | Time Complexity | Space |
|-----------|----------------|-------|
| Add Edge | O(1) | O(V + E) |
| Find Edge | O(degree(v)) | |
| List Neighbors | O(degree(v)) | |
| Memory | - | O(V + E) |

### Adjacency Matrix Representation
| Operation | Time Complexity | Space |
|-----------|----------------|-------|
| Add Edge | O(1) | O(V²) |
| Find Edge | O(1) | |
| List Neighbors | O(V) | |
| Memory | - | O(V²) |

Where:
- V = Number of vertices
- E = Number of edges
- degree(v) = Number of edges incident to vertex v

### Common Traversal Algorithms
| Algorithm | Time | Space |
|-----------|------|-------|
| DFS | O(V + E) | O(V) |
| BFS | O(V + E) | O(V) |
