#include <unordered_map>

template<typename T>
class DisjointSet {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;
    size_t set_count;

public:
    DisjointSet() : set_count(0) {}

    // Create a set with a single element
    void makeSet(const T& element) {
        if (parent.find(element) == parent.end()) {
            parent[element] = element;
            rank[element] = 0;
            set_count++;
        }
    }

    // Find with path compression
    T find(const T& element) {
        // Auto-create if doesn't exist
        if (parent.find(element) == parent.end()) {
            makeSet(element);
            return element;
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

        // Union by rank
        if (rank[root_a] < rank[root_b]) {
            parent[root_a] = root_b;
        } else if (rank[root_a] > rank[root_b]) {
            parent[root_b] = root_a;
        } else {
            parent[root_b] = root_a;
            rank[root_a]++;
        }
        
        set_count--;  // One less set after union
        return true;
    }

    // Check if two elements are in the same set
    bool isConnected(const T& a, const T& b) {
        return find(a) == find(b);
    }

    // Get number of disjoint sets - O(1)!
    size_t getNumberOfSets() const {
        return set_count;
    }

    // Check if element exists
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
        set_count = 0;
    }

    std::vector<T> getSetMembers(const T& element) {
        T root = find(element);
        std::vector<T> members;
        for (const auto& pair : parent) {
            if (find(pair.first) == root) {
                members.push_back(pair.first);
            }
        }
        return members;
    }

};
