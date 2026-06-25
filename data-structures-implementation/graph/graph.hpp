#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>

template<typename T>
class DirectedGraph {
private:
    // Using adjacency list representation
    std::unordered_map<T, std::list<T>> adjLists;
    std::unordered_map<T, int> indegree;
    std::unordered_set<T> vertices;

public:
    // Default constructor
    DirectedGraph() = default;
    
    // Add a vertex to the graph
    void addVertex(const T& vertex) {
        if (vertices.find(vertex) == vertices.end()) {
            vertices.insert(vertex);
            adjLists[vertex] = std::list<T>();
            indegree[vertex] = 0;
        }
    }
    
    // Add directed edge from source to destination
    void addEdge(const T& src, const T& dest) {
        // Add vertices if they don't exist
        addVertex(src);
        addVertex(dest);
        
        // Add edge
        adjLists[src].push_back(dest);
        
        // Update indegree
        indegree[dest]++;
    }
    
    // Remove a vertex and all its associated edges
    void removeVertex(const T& vertex) {
        if (vertices.find(vertex) == vertices.end()) {
            return;
        }
        
        // Remove all outgoing edges
        adjLists.erase(vertex);
        indegree.erase(vertex);
        vertices.erase(vertex);
        
        // Remove all incoming edges to this vertex
        for (auto& pair : adjLists) {
            pair.second.remove(vertex);
            // Note: This can be optimized with reverse adjacency list
        }
        
        // Update indegrees
        for (auto it = indegree.begin(); it != indegree.end(); ) {
            if (vertices.find(it->first) == vertices.end()) {
                it = indegree.erase(it);
            } else {
                ++it;
            }
        }
    }
    
    // Remove an edge
    void removeEdge(const T& src, const T& dest) {
        if (hasVertex(src) && hasVertex(dest)) {
            adjLists[src].remove(dest);
            if (indegree[dest] > 0) {
                indegree[dest]--;
            }
        }
    }
    
    // Check if vertex exists
    bool hasVertex(const T& vertex) const {
        return vertices.find(vertex) != vertices.end();
    }
    
    // Check if edge exists
    bool hasEdge(const T& src, const T& dest) const {
        if (!hasVertex(src) || !hasVertex(dest)) {
            return false;
        }
        
        const auto& neighbors = adjLists.at(src);
        return std::find(neighbors.begin(), neighbors.end(), dest) != neighbors.end();
    }
    
    // Get neighbors of a vertex
    const std::list<T>& getNeighbors(const T& vertex) const {
        static const std::list<T> emptyList;
        if (!hasVertex(vertex)) {
            return emptyList;
        }
        return adjLists.at(vertex);
    }
    
    // Get in-degree of a vertex
    int getInDegree(const T& vertex) const {
        if (!hasVertex(vertex)) {
            return -1; // Or throw exception
        }
        return indegree.at(vertex);
    }
    
    // Get out-degree of a vertex
    int getOutDegree(const T& vertex) const {
        if (!hasVertex(vertex)) {
            return -1; // Or throw exception
        }
        return adjLists.at(vertex).size();
    }
    
    // Get all vertices
    const std::unordered_set<T>& getVertices() const {
        return vertices;
    }
    
    // Get number of vertices
    size_t getVertexCount() const {
        return vertices.size();
    }
    
    // Get number of edges
    size_t getEdgeCount() const {
        size_t count = 0;
        for (const auto& pair : adjLists) {
            count += pair.second.size();
        }
        return count;
    }
    
    
    // Check if graph is DAG (Directed Acyclic Graph)
    bool isDAG() const {
        try {
            topologicalSort();
            return true;
        } catch (const std::runtime_error&) {
            return false;
        }
    }
    
    // Print graph representation
    void printGraph() const {
        for (const auto& vertex : vertices) {
            std::cout << vertex << " -> ";
            bool first = true;
            for (const auto& neighbor : adjLists.at(vertex)) {
                if (!first) std::cout << ", ";
                std::cout << neighbor;
                first = false;
            }
            std::cout << std::endl;
        }
    }
};

// // Example usage
// int main() {
//     // Example 1: Integer graph
//     DirectedGraph<int> intGraph;
    
//     intGraph.addEdge(5, 2);
//     intGraph.addEdge(5, 0);
//     intGraph.addEdge(4, 0);
//     intGraph.addEdge(4, 1);
//     intGraph.addEdge(2, 3);
//     intGraph.addEdge(3, 1);
    
//     std::cout << "Integer Graph:" << std::endl;
//     intGraph.printGraph();
    
//     std::cout << "\nTopological Sort: ";
//     try {
//         auto topoOrder = intGraph.topologicalSort();
//         for (const auto& vertex : topoOrder) {
//             std::cout << vertex << " ";
//         }
//         std::cout << std::endl;
//     } catch (const std::exception& e) {
//         std::cout << e.what() << std::endl;
//     }
    
//     // Example 2: String graph
//     DirectedGraph<std::string> stringGraph;
    
//     stringGraph.addEdge("A", "B");
//     stringGraph.addEdge("A", "C");
//     stringGraph.addEdge("B", "D");
//     stringGraph.addEdge("C", "D");
//     stringGraph.addEdge("D", "E");
    
//     std::cout << "\nString Graph:" << std::endl;
//     stringGraph.printGraph();
    
//     std::cout << "\nDFS traversal from A: ";
//     stringGraph.dfs("A", [](const std::string& vertex) {
//         std::cout << vertex << " ";
//     });
//     std::cout << std::endl;
    
//     std::cout << "BFS traversal from A: ";
//     stringGraph.bfs("A", [](const std::string& vertex) {
//         std::cout << vertex << " ";
//     });
//     std::cout << std::endl;
    
//     return 0;
// }
