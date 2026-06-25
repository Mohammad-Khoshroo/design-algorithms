#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>


// Kahn's algorithm implementation
template<typename T>
std::vector<T> topologicalSortKahn(const DirectedGraph<T>& graph) {
    if (graph.getVertexCount() == 0) {
        return {};
    }
    
    // Create a copy of in-degrees
    std::unordered_map<T, int> inDegreeCopy;
    for (const auto& vertex : graph.getVertices()) {
        inDegreeCopy[vertex] = graph.getInDegree(vertex);
    }
    
    // Queue for vertices with zero in-degree
    std::queue<T> zeroInDegreeQueue;
    
    // Find all vertices with zero in-degree
    for (const auto& vertex : graph.getVertices()) {
        if (inDegreeCopy[vertex] == 0) {
            zeroInDegreeQueue.push(vertex);
        }
    }
    
    std::vector<T> result;
    
    // Process vertices in topological order
    while (!zeroInDegreeQueue.empty()) {
        T current = zeroInDegreeQueue.front();
        zeroInDegreeQueue.pop();
        result.push_back(current);
        
        // Reduce in-degree of all neighbors
        for (const auto& neighbor : graph.getNeighbors(current)) {
            inDegreeCopy[neighbor]--;
            // If in-degree becomes zero, add to queue
            if (inDegreeCopy[neighbor] == 0) {
                zeroInDegreeQueue.push(neighbor);
            }
        }
    }
    
    // Check for cycles
    if (result.size() != graph.getVertexCount()) {
        throw std::runtime_error("Graph has a cycle. Topological sort not possible.");
    }
    
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
    
//     std::cout << "\n=== Kahn's Algorithm ===" << std::endl;
//     try {
//         auto kahnOrder = topologicalSortKahn(courseGraph);
//         std::cout << "Course sequence (Kahn):" << std::endl;
//         for (size_t i = 0; i < kahnOrder.size(); ++i) {
//             std::cout << (i + 1) << ". " << kahnOrder[i] << std::endl;
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
    
//     std::cout << "\nTrying Kahn's algorithm on cyclic graph:" << std::endl;
//     try {
//         auto result = topologicalSortKahn(cyclicGraph);
//         std::cout << "Unexpected success!" << std::endl;
//     } catch (const std::exception& e) {
//         std::cout << "Caught expected error: " << e.what() << std::endl;
//     }
    
//     return 0;
// }
