# Disjoint-Set (Union-Find) Data Structure

## Introduction

The **Disjoint-Set** data structure (also known as **Union-Find**) is one of the most useful and elegant structures in computer science. It serves as the foundation for important algorithms like **Kruskal's algorithm** for finding the Minimum Spanning Tree (MST).

In this document, we'll explain the concept thoroughly and provide implementations in Python, C, and C++.

---

## Conceptual Overview

### Definition and Use Case

Assume you have $ N $ distinct elements initially placed in separate sets. You want to perform two primary operations:

1. **Union**: Merge two sets into one.
2. **Find**: Determine which set an element belongs to, or whether two elements are in the same set.

This data structure performs these operations very efficiently—almost in constant time.

Suppose we have 5 elements: `{0, 1, 2, 3, 4}`.
- **Initially:** Each element is in its own separate set: `{0}, {1}, {2}, {3}, {4}`.
- **After `Union(1, 2)`:** `{0}, {1, 2}, {3}, {4}`.
- **After `Union(3, 4)`:** `{0}, {1, 2}, {3, 4}`.
- **After `Union(2, 4)`:** `{0}, {1, 2, 3, 4}`.

### Why So Fast?

When we combine **Path Compression** with **Union by Rank**, the trees become extremely flat. This means:
- Tree heights stay very small (usually less than 5!)
- Finding the root takes nearly one step
- That's why the complexity reaches α(n), which is practically constant!

### Visual Representation

The simplest way to represent these sets is using a **forest of trees**:
- Each set is represented by a tree.
- Each element is a node in the tree.
- The root of the tree is the **representative** of the set.
- Each node has a pointer to its parent (`parent`).

### Core Operations

- **MakeSet(x)**: Creates a new set containing only element $ x $. Initially, `parent[x] = x`.
- **Find(x)**: Traverses from $ x $ up to the root to identify the representative of the set.
- **Union(x, y)**: Finds roots of $ x $ and $ y $, then merges their trees if they belong to different sets.

### Basic Implementation Details

In this structure, each set is represented as a **directed tree** where each node points to its parent. The root node points to itself.

- **Operation `find(u)`**: To find the representative (leader) of the set containing node `u`, start from the node and traverse upward until reaching the root (where `parent(u) == u`).
- **Operation `union(a, b)`**: To merge two sets, first find their roots ($r_1$ and $r_2$), then make one root the parent of the other. In basic implementation, without specific conditions, the first root becomes a child of the second.

---

## Improving Implementation with Height/Rank (Union by Height/Rank)

To prevent creating very tall trees (which would slow down operations), we use the **Union by Height** strategy. In this method, when merging, the tree with smaller height becomes a subtree of the tree with greater height.

- **Union Rule**: If the height of the first tree is greater, the second root becomes a child of the first root. Otherwise, the first root becomes a child of the second root.
- **Height Change**: The total height of the tree increases (by 1 unit) only when two trees with **equal heights** are merged.
- **Mathematical Relationship**: A tree with height $h$ contains at least $2^h$ nodes. This can be proven by induction:
  - For combining two trees with height $h-1$, the number of nodes equals: $2^{h-1} + 2^{h-1} = 2^h$.
- **Result**: This improvement ensures that the height of a tree with $n$ nodes remains $O(\log n)$.

Why `rank` instead of `height`?
- `rank` only changes during `union` operations
- Calculating actual `height` is expensive as it requires checking the entire subtree
- `rank` provides a good approximation of height with better performance

---

## Runtime Complexity Analysis

With the "Union by Height" improvement, the time complexities are as follows:

- **Complexity of `find(u)`**: Since the tree height is at most $O(\log n)$, traversing from a node to the root takes at most this much time. Therefore, the runtime is $O(\log n)$.
- **Complexity of `union(a, b)`**:
  - This operation involves two calls to the `find` function to locate the roots. Thus, its time is $O(\max(h[a], h[b]))$ or simply $O(\log n)$.
  - **Best Case**: If the input nodes ($a$ and $b$) are already roots, the operation completes in constant time $O(1)$.

**Final Note**: While these slides don't mention "Path Compression," combining it with this method can reduce complexity to the inverse Ackermann function (essentially constant time).

---

## Code Implementations

All implementations include the core methods `find()` and `union()` with optimizations applied.

### Python Implementation

```python
class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])  # Path compression
        return self.parent[i]

    def union(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)

        if root_i == root_j:
            return

        if self.rank[root_i] < self.rank[root_j]:
            self.parent[root_i] = root_j
        elif self.rank[root_i] > self.rank[root_j]:
            self.parent[root_j] = root_i
        else:
            self.parent[root_j] = root_i
            self.rank[root_i] += 1

# Example usage
if __name__ == "__main__":
    ds = DisjointSet(5)
    
    ds.union(0, 2)
    ds.union(4, 2)
    ds.union(3, 1)
    
    print("4 and 0:", "Same set" if ds.find(4) == ds.find(0) else "Different sets")
    print("1 and 0:", "Same set" if ds.find(1) == ds.find(0) else "Different sets")
```

### C Implementation

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int n;
} DisjointSet;

DisjointSet* createDisjointSet(int n) {
    DisjointSet *ds = malloc(sizeof(DisjointSet));
    ds->n = n;
    ds->parent = malloc(n * sizeof(int));
    ds->rank = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
    return ds;
}

int find(DisjointSet *ds, int i) {
    if (ds->parent[i] != i) {
        ds->parent[i] = find(ds, ds->parent[i]);  // Path compression
    }
    return ds->parent[i];
}

void unionSets(DisjointSet *ds, int i, int j) {
    int root_i = find(ds, i);
    int root_j = find(ds, j);

    if (root_i == root_j) return;

    if (ds->rank[root_i] < ds->rank[root_j]) {
        ds->parent[root_i] = root_j;
    } else if (ds->rank[root_i] > ds->rank[root_j]) {
        ds->parent[root_j] = root_i;
    } else {
        ds->parent[root_j] = root_i;
        ds->rank[root_i]++;
    }
}

int main() {
    int n = 5;
    DisjointSet *ds = createDisjointSet(n);

    unionSets(ds, 0, 2);
    unionSets(ds, 4, 2);
    unionSets(ds, 3, 1);

    printf("4 and 0: %s\n", find(ds, 4) == find(ds, 0) ? "Same set" : "Different sets");

    free(ds->parent);
    free(ds->rank);
    free(ds);

    return 0;
}
```

### C++ Implementation

```cpp
#include <iostream>
#include <vector>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);  // Path compression
        }
        return parent[i];
    }

    void unionSets(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i == root_j) return;

        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else if (rank[root_i] > rank[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank[root_i]++;
        }
    }
};

int main() {
    DisjointSet ds(5);

    ds.unionSets(0, 2);
    ds.unionSets(4, 2);
    ds.unionSets(3, 1);

    std::cout << "4 and 0: " << (ds.find(4) == ds.find(0) ? "Same set" : "Different sets") << "\n";

    return 0;
}
```

---

## Understanding Inverse Ackermann Function $\alpha(n)$

We often see the complexity expressed as $O(\alpha(n))$. Let's demystify what it means:

### What Is the Ackermann Function?

It's a recursive function defined as follows:
$$
A(m, n) =
\begin{cases}
n + 1 & \text{if } m = 0 \\
A(m - 1, 1) & \text{if } m > 0 \text{ and } n = 0 \\
A(m - 1, A(m, n - 1)) & \text{if } m > 0 \text{ and } n > 0
\end{cases}
$$

It grows extremely fast—even $A(4, 4)$ is astronomically large.

### What Is Its Inverse?

The inverse Ackermann function $\alpha(n)$ is defined as the smallest integer $k$ such that $A(k, k) \geq n$.

Values grow so slowly that for all practical purposes:
$$
\alpha(n) \leq 4
$$

Thus, saying something takes $O(\alpha(n))$ time essentially means it's almost constant.

---

## Real-world Applications

Here are some key applications where Disjoint-Set shines:

### a) Kruskal's MST Algorithm

Used to detect cycles when building a minimum spanning tree incrementally by adding edges sorted by weight.

### b) Connected Components Detection

Efficiently tracks connected components in dynamic graphs as edges are added or removed.

### c) Image Segmentation

Groups pixels based on similarity criteria during image processing tasks.

### d) Dynamic Connectivity Problems

Tracks connectivity between nodes in systems like networks or social media platforms where connections change over time.

### e) Social Network Groups

Example: Tracking friend groups in a social network:
```python
users = ["Alice", "Bob", "Charlie", "David"]
# Map names to indices
name_to_index = {name: i for i, name in enumerate(users)}
ds = DisjointSet(len(users))

# Alice and Bob become friends
ds.union(name_to_index["Alice"], name_to_index["Bob"])
# Charlie and David become friends  
ds.union(name_to_index["Charlie"], name_to_index["David"])

# Check if Alice and Charlie are in same group
print(ds.find(name_to_index["Alice"]) == ds.find(name_to_index["Charlie"]))
```

---

## Technical Notes

### Alternative Optimization: Union by Size

Instead of tracking ranks, track subtree sizes and merge smaller subtrees into larger ones. Performance is similar but sometimes easier to implement.

### Comparison with DFS/BFS

While DFS/BFS work well for static graphs, Disjoint-Set excels at handling **dynamic changes**, offering near-instant updates after edge insertions or deletions.

For dynamic graphs:
- **DFS/BFS**: Must re-run after each edge addition - O(V+E) 
- **Disjoint-Set**: Each `union` or `find` is nearly O(1)
- For algorithms like Kruskal with many operations, Disjoint-Set is much better

### Limitations

- Cannot efficiently split merged sets.
- Doesn't support listing members of a component without traversing the entire dataset.