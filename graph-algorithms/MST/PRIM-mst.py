import heapq

def prim_mst(graph, start_node):
    
    mst_edges = []      
    visited = set()     
    total_weight = 0    

    min_heap = [(0, start_node, None)]
    
    while min_heap:
        weight, current_node, parent = heapq.heappop(min_heap)
        
        if current_node in visited:
            continue
            
        visited.add(current_node)
        total_weight += weight
        
        if parent is not None:
            mst_edges.append((parent, current_node, weight))
            
        for neighbor, edge_weight in graph[current_node]:
            if neighbor not in visited:
                heapq.heappush(min_heap, (edge_weight, neighbor, current_node))
                
    return mst_edges, total_weight

graph = {
    'A': [('B', 1), ('C', 4), ('D', 5)],
    'B': [('A', 1), ('C', 3)],
    'C': [('B', 3), ('A', 4), ('D', 6)],
    'D': [('A', 5), ('C', 6)]
}

mst, total_cost = prim_mst(graph, 'A')

print("Edges in Minimum Spanning Tree:")
for u, v, weight in mst:
    print(f"{u} - {v} (weight: {weight})")
    
print("\nTotal MST Weight:", total_cost)
