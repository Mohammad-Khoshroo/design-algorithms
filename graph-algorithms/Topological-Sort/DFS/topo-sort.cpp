#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>

// DFS-based topological sort implementation
template<typename T>
std::vector<T> topologicalSortDFS(const DirectedGraph<T>& graph) {
    if (graph.getVertexCount() == 0) {
        return {};
    }
    
    std::unordered_map<T, int> state; // 0: unvisited, 1: visiting, 2: visited
    std::vector<T> result;
    bool hasCycle = false;
    
    // Initialize all vertices as unvisited
    for (const auto& vertex : graph.getVertices()) {
        state[vertex] = 0;
    }
    
    // Helper function for DFS
    std::function<void(const T&)> dfsVisit = [&](const T& vertex) {
        if (hasCycle) return;
        
        state[vertex] = 1; // Mark as visiting
        
        // Visit all neighbors
        for (const auto& neighbor : graph.getNeighbors(vertex)) {
            if (state[neighbor] == 0) {
                // Unvisited vertex
                dfsVisit(neighbor);
            } else if (state[neighbor] == 1) {
                // Back edge detected - cycle found
                hasCycle = true;
                return;
            }
        }
        
        state[vertex] = 2; // Mark as visited
        result.push_back(vertex);
    };
    
    // Perform DFS on all unvisited vertices
    for (const auto& vertex : graph.getVertices()) {
        if (state[vertex] == 0) {
            dfsVisit(vertex);
            if (hasCycle) {
                throw std::runtime_error("Graph contains a cycle. Topological sort not possible.");
            }
        }
    }
    
    // Reverse the result to get correct topological order
    std::reverse(result.begin(), result.end());
    return result;
}


// // Example usage
// int main() {
//     DirectedGraph<std::string> courseGraph;
    
//     // Add course prerequisites
//     courseGraph.addEdge("Mathematics", "Algorithms");
//     courseGraph.addEdge("Mathematics", "Data Structures");
//     courseGraph.addEdge("Algorithms", "Machine Learning");
//     courseGraph.addEdge("Data Structures", "Database Systems");
//     courseGraph.addEdge("Data Structures", "Operating Systems");
//     courseGraph.addEdge("Operating Systems", "Distributed Systems");
    
//     std::cout << "Course Prerequisites Graph:" << std::endl;
//     courseGraph.printGraph();
    
//     std::cout << "\n=== DFS-Based Topological Sort ===" << std::endl;
//     try {
//         auto dfsOrder = topologicalSortDFS(courseGraph);
//         std::cout << "Course sequence (DFS):" << std::endl;
//         for (size_t i = 0; i < dfsOrder.size(); ++i) {
//             std::cout << (i + 1) << ". " << dfsOrder[i] << std::endl;
//         }
//     } catch (const std::exception& e) {
//         std::cout << "Error: " << e.what() << std::endl;
//     }
    
    
//     // Test with a cyclic graph
//     std::cout << "\n=== Testing with Cyclic Graph ===" << std::endl;
//     DirectedGraph<int> cyclicGraph;
//     cyclicGraph.addEdge(1, 2);
//     cyclicGraph.addEdge(2, 3);
//     cyclicGraph.addEdge(3, 1); // Creates a cycle
    
//     std::cout << "Cyclic Graph:" << std::endl;
//     cyclicGraph.printGraph();
    
//     std::cout << "\nTrying DFS-based sort on cyclic graph:" << std::endl;
//     try {
//         auto result = topologicalSortDFS(cyclicGraph);
//         std::cout << "Unexpected success!" << std::endl;
//     } catch (const std::exception& e) {
//         std::cout << "Caught expected error: " << e.what() << std::endl;
//     }
    
    
//     return 0;
// }
