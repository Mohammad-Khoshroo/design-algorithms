# 📘 Topological Sorting

## 🔍 What is Topological Sorting?

**Topological Sorting** is a linear ordering of vertices in a **Directed Acyclic Graph (DAG)** such that for every directed edge `u -> v`, vertex `u` comes before `v` in the ordering.

In simpler terms:
> If there are dependencies between tasks or items, topological sorting arranges them so that all dependencies come before the dependent item.

It's useful in scheduling jobs, resolving module dependencies, course prerequisites, etc.

---

## 🧠 Key Concepts Before Diving In

### Directed Graph (Digraph)

A graph where edges have direction. Each edge connects two nodes but has an orientation from one node to another.

Example representation:

```python
graph = {
    'A': ['B', 'C'],
    'B': ['D'],
    'C': [],
    'D': []
}
```

### Types of Edges in DFS Traversal on Digraphs

When performing Depth First Search (DFS) on a digraph, we classify edges into four types:

| Type         | Description |
|--------------|-------------|
| Tree Edge    | Part of the DFS traversal tree |
| Back Edge    | Points from descendant to ancestor → indicates cycle |
| Forward Edge | Points from ancestor to proper descendant |
| Cross Edge   | All other edges |

💡 **Important Note**:  
If any **back edge exists**, the graph contains a **cycle**, and hence **topological sort is impossible**.

### Directed Acyclic Graph (DAG)

A directed graph without cycles. Only DAGs can be topologically sorted.

---

## ⚙️ How Does Topological Sort Work?

There are two main algorithms used for topological sorting:

### 1. Kahn’s Algorithm (Based on BFS)

This algorithm uses **in-degree** counting:

#### Steps:
1. Compute in-degrees of all vertices.
2. Enqueue all vertices with in-degree zero (sources).
3. While queue is not empty:
   - Dequeue a vertex `v`.
   - Add `v` to result list.
   - For each neighbor `w` of `v`:
     - Decrease in-degree of `w` by 1.
     - If in-degree becomes zero, enqueue `w`.

Time Complexity: $O(V + E)$

Space Complexity: $O(V)$

### 2. DFS-Based Approach

Uses post-order DFS traversal and stack:

#### Steps:
1. Perform DFS on unvisited nodes.
2. Push node onto stack after visiting all its neighbors.
3. Reverse the order of elements popped from stack.

Time Complexity: $O(V + E)$

Space Complexity: $O(V)$

Both approaches work efficiently on large graphs.

---

## 💻 Implementations

We'll provide clean implementations in Python, C++, and C below.

### ✅ Python Implementation (Using DFS)

```python
from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        self.graph = defaultdict(list)
        self.V = vertices

    def add_edge(self, u, v):
        self.graph[u].append(v)

    def topological_sort_util(self, v, visited, stack):
        visited[v] = True
        for i in self.graph[v]:
            if not visited[i]:
                self.topological_sort_util(i, visited, stack)
        stack.append(v)

    def topological_sort(self):
        visited = [False] * self.V
        stack = []

        for i in range(self.V):
            if not visited[i]:
                self.topological_sort_util(i, visited, stack)

        return stack[::-1]

# Example usage
g = Graph(6)
g.add_edge(5, 2)
g.add_edge(5, 0)
g.add_edge(4, 0)
g.add_edge(4, 1)
g.add_edge(2, 3)
g.add_edge(3, 1)

print("Topological Sort:", g.topological_sort())
```

---

### ✅ C++ Implementation (Using DFS)

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
public:
    Graph(int vertices);
    void addEdge(int u, int v);
    void topologicalSort();
};

Graph::Graph(int vertices) {
    V = vertices;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
}

void Graph::topologicalSort() {
    vector<bool> visited(V, false);
    stack<int> Stack;

    function<void(int)> dfs = [&](int v) {
        visited[v] = true;
        for (int i : adj[v])
            if (!visited[i])
                dfs(i);
        Stack.push(v);
    };

    for (int i = 0; i < V; ++i)
        if (!visited[i])
            dfs(i);

    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Topological Sort: ";
    g.topologicalSort();
    return 0;
}
```

---

### ✅ C Implementation (Using Kahn's Algorithm)

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node *front, *rear;
};

struct Node* newNode(int k) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = k;
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Queue* q, int k) {
    struct Node* temp = newNode(k);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

int dequeue(struct Queue* q) {
    if (q->front == NULL)
        return -1;
    struct Node* temp = q->front;
    int val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return val;
}

int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

void topologicalSort(int n, int adj[][n], int indegree[]) {
    struct Queue* q = createQueue();
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            enqueue(q, i);

    printf("Topological Sort: ");
    while (!isEmpty(q)) {
        int u = dequeue(q);
        printf("%d ", u);
        for (int v = 0; v < n; v++) {
            if (adj[u][v]) {
                indegree[v]--;
                if (indegree[v] == 0)
                    enqueue(q, v);
            }
        }
    }
}

int main() {
    int n = 6;
    int adj[6][6] = {{0}};
    int indegree[6] = {0};

    // Adding edges manually
    adj[5][2] = 1; indegree[2]++;
    adj[5][0] = 1; indegree[0]++;
    adj[4][0] = 1; indegree[0]++;
    adj[4][1] = 1; indegree[1]++;
    adj[2][3] = 1; indegree[3]++;
    adj[3][1] = 1; indegree[1]++;

    topologicalSort(n, adj, indegree);
    return 0;
}
```

---

## 📈 Time & Space Complexity Analysis

| Method             | Time Complexity | Space Complexity |
|--------------------|------------------|-------------------|
| DFS-based          | $O(V + E)$   | $O(V)$        |
| Kahn's Algorithm   | $O(V + E)$   | $O(V)$        |

Where:
- $V$ = number of vertices
- $E$ = number of edges

Both methods scale well even for very large graphs.

---

## 🧩 Applications of Topological Sorting

Here are some real-world scenarios where topological sort plays a crucial role:

### 1. Course Prerequisites
Arrange courses such that prerequisite courses appear before advanced ones.

### 2. Build Systems (Makefiles / Gradle)
Ensure dependencies like libraries or modules are compiled in correct order.

### 3. Task Scheduling
Used in project management tools (like PERT charts) to determine execution order based on task dependencies.

### 4. Data Serialization
Ordering fields during serialization to maintain logical consistency.

### 5. Dependency Resolution in Package Managers
For example, installing packages in correct dependency order (`npm install`, `pip install`, etc.)

### 6. Spreadsheet Calculations
Excel-like applications use topological sort to compute formulas in the right sequence.

---

## ⚡ Optimizations and Tips

### Use Adjacency Lists Instead of Matrices

Especially for sparse graphs, adjacency lists save memory and improve performance.

### Detect Cycles Early

During DFS, detect back edges early to stop unnecessary computation when dealing with possibly cyclic inputs.

### Parallelize Processing

In systems with multiple CPUs/core, parallelizing parts of Kahn’s algorithm may speed things up slightly.

---

Topological sorting is a fundamental concept in graph theory with wide applicability across software engineering, system design, and data processing pipelines.

Whether you're planning a curriculum, building a compiler, or designing a build system — understanding how to perform topological sort will give you powerful tools to manage dependencies and structures effectively.

---

## 📌 Final Notes

- Always check whether the input graph is a DAG before attempting to sort.
- Understand both DFS and Kahn’s methods thoroughly.
- Be mindful of space vs. time trade-offs depending on your application needs.
