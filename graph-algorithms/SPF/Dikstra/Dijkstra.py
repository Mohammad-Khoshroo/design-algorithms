import heapq

def dijkstra(graph, start_node):
    
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    
    priority_queue = [(0, start_node)]
    
    predecessors = {node: None for node in graph}
    
    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)
        
        if current_distance > distances[current_node]:
            continue
            
        for neighbor, weight in graph[current_node]:
            distance_through_current = current_distance + weight
            
            if distance_through_current < distances[neighbor]:
                distances[neighbor] = distance_through_current
                predecessors[neighbor] = current_node
                heapq.heappush(priority_queue, (distance_through_current, neighbor))
                
    return distances, predecessors

graph = {
    'A': [('B', 4), ('C', 10)],
    'B': [('C', 2)],
    'C': []
}

distances, predecessors = dijkstra(graph, 'A')

print("Shortest distances from source 'A':")
for node, distance in distances.items():
    print(f"To {node}: {distance}")
