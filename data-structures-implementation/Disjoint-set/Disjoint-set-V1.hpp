#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename T>
class DisjointSet {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;
    mutable std::unordered_map<T, std::unordered_set<T>> cached_members;
    mutable bool cache_valid = false;
    size_t set_count;  // Number of disjoint sets

    // Helper function to rebuild cache when needed
    void rebuildCache() const {
        if (cache_valid) return;
        
        cached_members.clear();
        for (const auto& pair : parent) {
            T root = find(pair.first);
            cached_members[root].insert(pair.first);
        }
        cache_valid = true;
    }

public:
    DisjointSet() : set_count(0) {}

    // Create a set with a single element
    void makeSet(const T& element) {
        if (parent.find(element) == parent.end()) {
            parent[element] = element;
            rank[element] = 0;
            set_count++;
            cache_valid = false;
        }
    }

    // Find with path compression
    T find(const T& element) {
        // Ensure element exists
        if (parent.find(element) == parent.end()) {
            makeSet(element);
        }
        
        if (parent[element] != element) {
            parent[element] = find(parent[element]);  // Path compression
        }
        return parent[element];
    }

    // Union by rank
    bool unionSets(const T& a, const T& b) {
        T root_a = find(a);
        T root_b = find(b);

        if (root_a == root_b) {
            return false;  // Already in the same set
        }

        if (rank[root_a] < rank[root_b]) {
            parent[root_a] = root_b;
        } else if (rank[root_a] > rank[root_b]) {
            parent[root_b] = root_a;
        } else {
            parent[root_b] = root_a;
            rank[root_a]++;
        }
        
        set_count--;
        cache_valid = false;
        return true;  // Successfully merged
    }

    // Check if two elements are in the same set
    bool isConnected(const T& a, const T& b) {
        return find(a) == find(b);
    }

    // Get all elements in the same set as given element
    std::unordered_set<T> getSetMembers(const T& element) {
        T root = find(element);
        rebuildCache();
        return cached_members[root];
    }

    // Get number of disjoint sets - O(1) time!
    size_t getNumberOfSets() const {
        return set_count;
    }

    // Get size of set containing element
    size_t getSetSize(const T& element) {
        T root = find(element);
        rebuildCache();
        return cached_members[root].size();
    }

    // Check if element exists in any set
    bool contains(const T& element) const {
        return parent.find(element) != parent.end();
    }

    // Get total number of elements
    size_t getTotalElements() const {
        return parent.size();
    }

    // Clear all data
    void clear() {
        parent.clear();
        rank.clear();
        cached_members.clear();
        set_count = 0;
        cache_valid = false;
    }
};

// Example usage
// #include <iostream>
// #include <string>

// int main() {
//     // Example 1: Using with integers
//     DisjointSet<int> ds_int;
    
//     for (int i = 1; i <= 5; i++) {
//         ds_int.makeSet(i);
//     }
    
//     ds_int.unionSets(1, 2);
//     ds_int.unionSets(4, 5);
//     ds_int.unionSets(2, 4);
    
//     std::cout << "Integer example:" << std::endl;
//     std::cout << "1 and 3 are " << (ds_int.isConnected(1, 3) ? "" : "not ") << "connected" << std::endl;
//     std::cout << "Number of sets: " << ds_int.getNumberOfSets() << std::endl;
//     std::cout << "Total elements: " << ds_int.getTotalElements() << std::endl;
    
//     // Example 2: Using with strings
//     DisjointSet<std::string> ds_string;
    
//     ds_string.makeSet("Alice");
//     ds_string.makeSet("Bob");
//     ds_string.makeSet("Charlie");
//     ds_string.makeSet("David");
    
//     ds_string.unionSets("Alice", "Bob");
//     ds_string.unionSets("Charlie", "David");
    
//     std::cout << "\nString example:" << std::endl;
//     std::cout << "Alice and Bob are " << (ds_string.isConnected("Alice", "Bob") ? "" : "not ") << "connected" << std::endl;
//     std::cout << "Alice and Charlie are " << (ds_string.isConnected("Alice", "Charlie") ? "" : "not ") << "connected" << std::endl;
//     std::cout << "Number of sets: " << ds_string.getNumberOfSets() << std::endl;
    
//     return 0;
// }
