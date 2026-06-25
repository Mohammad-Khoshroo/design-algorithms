from collections import deque
from typing import TypeVar, Generic, List, Set
from enum import Enum

T = TypeVar('T')

class NodeState(Enum):
    """Represents the state of a node during DFS traversal."""
    UNVISITED = 0
    VISITING = 1
    VISITED = 2

def topological_sort_kahn(graph: 'DirectedGraph[T]') -> List[T]:
    """
    Perform topological sort using Kahn's algorithm.
    
    Args:
        graph: A DirectedGraph instance
        
    Returns:
        A list representing the topological order of vertices
        
    Raises:
        ValueError: If the graph contains a cycle
    """
    if graph.is_empty():
        return []
    
    # Create a copy of in-degrees
    in_degree_copy: dict[T, int] = {vertex: graph.get_indegree(vertex) for vertex in graph.get_vertices()}
    
    # Queue for vertices with zero in-degree
    zero_in_degree_queue: deque[T] = deque()
    
    # Find all vertices with zero in-degree
    for vertex in graph.get_vertices():
        if in_degree_copy[vertex] == 0:
            zero_in_degree_queue.append(vertex)
    
    result: List[T] = []
    
    # Process vertices in topological order
    while zero_in_degree_queue:
        current = zero_in_degree_queue.popleft()
        result.append(current)
        
        # Reduce in-degree of all neighbors
        for neighbor in graph.get_neighbors(current):
            in_degree_copy[neighbor] -= 1
            # If in-degree becomes zero, add to queue
            if in_degree_copy[neighbor] == 0:
                zero_in_degree_queue.append(neighbor)
    
    # Check for cycles
    if len(result) != graph.get_vertex_count():
        raise ValueError("Graph has a cycle. Topological sort not possible.")
    
    return result

# # Example usage
# if __name__ == "__main__":
#     # Example 1: Course prerequisites
#     course_graph = DirectedGraph[str]()
    
#     # Add course dependencies
#     course_graph.add_edge("Mathematics", "Algorithms")
#     course_graph.add_edge("Mathematics", "Data Structures")
#     course_graph.add_edge("Algorithms", "Machine Learning")
#     course_graph.add_edge("Data Structures", "Database Systems")
#     course_graph.add_edge("Data Structures", "Operating Systems")
#     course_graph.add_edge("Operating Systems", "Distributed Systems")
    
#     print("Course Prerequisites Graph:")
#     print(course_graph)
#     print()
    
#     print("=== DFS-Based Topological Sort ===")
#     try:
#         dfs_order = topological_sort_dfs(course_graph)
#         print("Course sequence (DFS):")
#         for i, course in enumerate(dfs_order, 1):
#             print(f"{i}. {course}")
#     except ValueError as e:
#         print(f"Error: {e}")
#     print()
    
#     print("=== Kahn's Algorithm ===")
#     try:
#         kahn_order = topological_sort_kahn(course_graph)
#         print("Course sequence (Kahn):")
#         for i, course in enumerate(kahn_order, 1):
#             print(f"{i}. {course}")
#     except ValueError as e:
#         print(f"Error: {e}")
#     print()
    
#     # Example 2: Testing with cyclic graph
#     print("=== Testing with Cyclic Graph ===")
#     cyclic_graph = DirectedGraph[int]()
#     cyclic_graph.add_edge(1, 2)
#     cyclic_graph.add_edge(2, 3)
#     cyclic_graph.add_edge(3, 1)  # Creates a cycle
    
#     print("Cyclic Graph:")
#     print(cyclic_graph)
#     print()
    
#     print("Trying DFS-based sort on cyclic graph:")
#     try:
#         result = topological_sort_dfs(cyclic_graph)
#         print("Unexpected success!")
#     except ValueError as e:
#         print(f"Caught expected error: {e}")
#     print()
    
#     print("Trying Kahn's algorithm on cyclic graph:")
#     try:
#         result = topological_sort_kahn(cyclic_graph)
#         print("Unexpected success!")
#     except ValueError as e:
#         print(f"Caught expected error: {e}")
