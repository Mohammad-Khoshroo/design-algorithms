from collections import defaultdict, deque
from typing import TypeVar, Generic, Set, List, Iterator, Optional, Any

T = TypeVar('T')

class DirectedGraph(Generic[T]):
    """
    A general-purpose directed graph implementation using adjacency list representation.
    """
    
    def __init__(self):
        """Initialize an empty directed graph."""
        self._adj_lists: defaultdict[T, List[T]] = defaultdict(list)
        self._indegree: defaultdict[T, int] = defaultdict(int)
        self._vertices: Set[T] = set()
    
    def add_vertex(self, vertex: T) -> None:
        """
        Add a vertex to the graph.
        
        Args:
            vertex: The vertex to add
        """
        if vertex not in self._vertices:
            self._vertices.add(vertex)
            # Ensure entries exist in our dictionaries
            self._adj_lists[vertex]  # This creates an empty list if not exists
            self._indegree[vertex]   # This sets to 0 if not exists
    
    def add_edge(self, src: T, dest: T) -> None:
        """
        Add a directed edge from source to destination.
        
        Args:
            src: Source vertex
            dest: Destination vertex
        """
        # Add vertices if they don't exist
        self.add_vertex(src)
        self.add_vertex(dest)
        
        # Add edge
        self._adj_lists[src].append(dest)
        
        # Update indegree
        self._indegree[dest] += 1
    
    def remove_vertex(self, vertex: T) -> None:
        """
        Remove a vertex and all its associated edges.
        
        Args:
            vertex: The vertex to remove
        """
        if vertex not in self._vertices:
            return
        
        # Remove all outgoing edges
        # First decrease indegree of all neighbors
        for neighbor in self._adj_lists[vertex]:
            self._indegree[neighbor] -= 1
        
        # Remove the vertex from adjacency lists of other vertices
        for v in self._vertices:
            self._adj_lists[v] = [n for n in self._adj_lists[v] if n != vertex]
        
        # Remove the vertex itself
        del self._adj_lists[vertex]
        del self._indegree[vertex]
        self._vertices.remove(vertex)
    
    def remove_edge(self, src: T, dest: T) -> None:
        """
        Remove an edge from source to destination.
        
        Args:
            src: Source vertex
            dest: Destination vertex
        """
        if src in self._vertices and dest in self._vertices:
            if dest in self._adj_lists[src]:
                self._adj_lists[src].remove(dest)
                self._indegree[dest] -= 1
    
    def has_vertex(self, vertex: T) -> bool:
        """
        Check if a vertex exists in the graph.
        
        Args:
            vertex: The vertex to check
            
        Returns:
            True if vertex exists, False otherwise
        """
        return vertex in self._vertices
    
    def has_edge(self, src: T, dest: T) -> bool:
        """
        Check if an edge exists from source to destination.
        
        Args:
            src: Source vertex
            dest: Destination vertex
            
        Returns:
            True if edge exists, False otherwise
        """
        return (src in self._vertices and 
                dest in self._vertices and 
                dest in self._adj_lists[src])
    
    def get_neighbors(self, vertex: T) -> List[T]:
        """
        Get all neighbors (outgoing edges) of a vertex.
        
        Args:
            vertex: The vertex to get neighbors for
            
        Returns:
            List of neighboring vertices
        """
        if vertex not in self._vertices:
            return []
        return list(self._adj_lists[vertex])
    
    def get_indegree(self, vertex: T) -> int:
        """
        Get the in-degree of a vertex.
        
        Args:
            vertex: The vertex to get in-degree for
            
        Returns:
            In-degree of the vertex
        """
        if vertex not in self._vertices:
            return 0
        return self._indegree[vertex]
    
    def get_outdegree(self, vertex: T) -> int:
        """
        Get the out-degree of a vertex.
        
        Args:
            vertex: The vertex to get out-degree for
            
        Returns:
            Out-degree of the vertex
        """
        if vertex not in self._vertices:
            return 0
        return len(self._adj_lists[vertex])
    
    def get_vertices(self) -> Set[T]:
        """
        Get all vertices in the graph.
        
        Returns:
            Set of all vertices
        """
        return self._vertices.copy()
    
    def get_vertex_count(self) -> int:
        """
        Get the number of vertices in the graph.
        
        Returns:
            Number of vertices
        """
        return len(self._vertices)
    
    def get_edge_count(self) -> int:
        """
        Get the number of edges in the graph.
        
        Returns:
            Number of edges
        """
        return sum(len(neighbors) for neighbors in self._adj_lists.values())
    
    def is_empty(self) -> bool:
        """
        Check if the graph is empty.
        
        Returns:
            True if graph has no vertices, False otherwise
        """
        return len(self._vertices) == 0
    
    def clear(self) -> None:
        """Clear the graph, removing all vertices and edges."""
        self._adj_lists.clear()
        self._indegree.clear()
        self._vertices.clear()
    
    def copy(self) -> 'DirectedGraph[T]':
        """
        Create a copy of the graph.
        
        Returns:
            A new DirectedGraph instance with the same structure
        """
        new_graph = DirectedGraph[T]()
        new_graph._adj_lists = defaultdict(list)
        new_graph._indegree = defaultdict(int)
        new_graph._vertices = self._vertices.copy()
        
        for vertex, neighbors in self._adj_lists.items():
            new_graph._adj_lists[vertex] = list(neighbors)
            
        for vertex, degree in self._indegree.items():
            new_graph._indegree[vertex] = degree
            
        return new_graph
    
    def __len__(self) -> int:
        """Return the number of vertices."""
        return len(self._vertices)
    
    def __contains__(self, vertex: T) -> bool:
        """Check if vertex is in the graph."""
        return self.has_vertex(vertex)
    
    def __iter__(self) -> Iterator[T]:
        """Iterate over all vertices."""
        return iter(self._vertices)
    
    def __repr__(self) -> str:
        """String representation of the graph."""
        if self.is_empty():
            return "DirectedGraph()"
        
        edges = []
        for src in self._vertices:
            for dest in self._adj_lists[src]:
                edges.append(f"({src}, {dest})")
        
        return f"DirectedGraph([{', '.join(edges)}])"
    
    def __str__(self) -> str:
        """Human-readable string representation."""
        if self.is_empty():
            return "Empty Directed Graph"
        
        lines = []
        for vertex in sorted(self._vertices, key=str):
            neighbors = ', '.join(str(n) for n in self._adj_lists[vertex])
            lines.append(f"{vertex} -> {neighbors if neighbors else 'None'}")
        
        return '\n'.join(lines)

# # Example usage
# if __name__ == "__main__":
#     # Create a graph with integer vertices
#     g = DirectedGraph[int]()
    
#     # Add vertices and edges
#     g.add_edge(1, 2)
#     g.add_edge(1, 3)
#     g.add_edge(2, 4)
#     g.add_edge(3, 4)
#     g.add_edge(4, 5)
    
#     print("Graph structure:")
#     print(g)
#     print()
    
#     # Test various methods
#     print(f"Number of vertices: {g.get_vertex_count()}")
#     print(f"Number of edges: {g.get_edge_count()}")
#     print(f"Vertices: {sorted(g.get_vertices())}")
#     print()
    
#     # Check degrees
#     for vertex in sorted(g.get_vertices()):
#         print(f"Vertex {vertex}: in-degree={g.get_indegree(vertex)}, "
#               f"out-degree={g.get_outdegree(vertex)}")
#     print()
    
#     # Check neighbors
#     for vertex in sorted(g.get_vertices()):
#         neighbors = g.get_neighbors(vertex)
#         print(f"Neighbors of {vertex}: {neighbors}")
#     print()
    
#     # Test edge existence
#     print(f"Edge from 1 to 2 exists: {g.has_edge(1, 2)}")
#     print(f"Edge from 2 to 1 exists: {g.has_edge(2, 1)}")
#     print()
    
#     # Test vertex existence
#     print(f"Vertex 3 exists: {g.has_vertex(3)}")
#     print(f"Vertex 6 exists: {g.has_vertex(6)}")
#     print()
    
#     # Create a graph with string vertices
#     sg = DirectedGraph[str]()
#     sg.add_edge("A", "B")
#     sg.add_edge("B", "C")
#     sg.add_edge("A", "C")
    
#     print("String graph:")
#     print(sg)
