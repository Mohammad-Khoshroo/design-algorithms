#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int n;
    int set_count;
} DisjointSet;

// Create a disjoint set structure with n elements (0 to n-1)
DisjointSet* createDisjointSet(int n) {
    DisjointSet *ds = malloc(sizeof(DisjointSet));
    ds->n = n;
    ds->set_count = n;
    ds->parent = malloc(n * sizeof(int));
    ds->rank = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;      // Initially, each element is its own parent
        ds->rank[i] = 0;        // Initial rank is zero
    }
    return ds;
}

// Find root with path compression
int find(DisjointSet *ds, int x) {
    if (x < 0 || x >= ds->n) return -1;  // Out of bounds check
    if (ds->parent[x] != x) {
        ds->parent[x] = find(ds, ds->parent[x]);  // Path compression
    }
    return ds->parent[x];
}

// Union two sets by rank
int unionSets(DisjointSet *ds, int x, int y) {
    int root_x = find(ds, x);
    int root_y = find(ds, y);

    if (root_x == -1 || root_y == -1) return -1;  // Index error
    if (root_x == root_y) return 0;               // Already in same set

    // Union by rank
    if (ds->rank[root_x] < ds->rank[root_y]) {
        ds->parent[root_x] = root_y;
    } else if (ds->rank[root_x] > ds->rank[root_y]) {
        ds->parent[root_y] = root_x;
    } else {
        ds->parent[root_y] = root_x;
        ds->rank[root_x]++;
    }

    ds->set_count--;  // One less set after successful union
    return 1;
}

// Check if two elements belong to the same set
int isConnected(DisjointSet *ds, int x, int y) {
    int root_x = find(ds, x);
    int root_y = find(ds, y);
    if (root_x == -1 || root_y == -1) return -1;  // Index error
    return root_x == root_y;
}

// Get number of disjoint sets - O(1) time complexity!
int getNumberOfSets(DisjointSet *ds) {
    return ds->set_count;
}

// Free allocated memory
void destroyDisjointSet(DisjointSet *ds) {
    free(ds->parent);
    free(ds->rank);
    free(ds);
}


int main() {
    int n = 5;
    DisjointSet *ds = createDisjointSet(n);

    // Union different nodes
    unionSets(ds, 0, 2);  // {0,2}
    unionSets(ds, 4, 2);  // {0,2,4}
    unionSets(ds, 3, 1);  // {3,1}

    // Check connectivity
    printf("Are 4 and 0 connected? %s\n", 
           isConnected(ds, 4, 0) ? "Yes" : "No");
    
    printf("Are 1 and 0 connected? %s\n", 
           isConnected(ds, 1, 0) ? "Yes" : "No");

    // Number of disjoint sets
    printf("Number of sets: %d\n", getNumberOfSets(ds));  // 2

    destroyDisjointSet(ds);
    return 0;
}
