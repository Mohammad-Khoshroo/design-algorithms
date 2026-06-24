class DisjointSet:
    def __init__(self):
        self.parent = {}
        self.rank = {}
        self.set_count = 0
    
    def make_set(self, element):
        """Create a new set containing only element"""
        if element not in self.parent:
            self.parent[element] = element
            self.rank[element] = 0
            self.set_count += 1
    
    def find(self, element):
        """Find root with path compression"""
        # Auto-create if doesn't exist
        if element not in self.parent:
            self.make_set(element)
            return element
            
        if self.parent[element] != element:
            self.parent[element] = self.find(self.parent[element])  # Path compression
        return self.parent[element]
    
    def union(self, x, y):
        """Union two sets by rank"""
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x == root_y:
            return False  # Already in same set
        
        # Union by rank
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1
        
        self.set_count -= 1
        return True
    
    def connected(self, x, y):
        """Check if two elements are in the same set"""
        return self.find(x) == self.find(y)
    
    def get_number_of_sets(self):
        """Get number of disjoint sets - O(1)"""
        return self.set_count
    
    def contains(self, element):
        """Check if element exists in any set"""
        return element in self.parent
    
    def get_set_members(self, element):
        """Get all members of the set containing element"""
        root = self.find(element)
        return [key for key in self.parent if self.find(key) == root]
    
    def clear(self):
        """Clear all sets"""
        self.parent.clear()
        self.rank.clear()
        self.set_count = 0


# # Example 1: Using with strings
# ds = DisjointSet()

# # Add people to different groups
# people = ["Alice", "Bob", "Charlie", "David", "Eve"]
# for person in people:
#     ds.make_set(person)

# # Union operations
# ds.union("Alice", "Bob")
# ds.union("Charlie", "David")
# ds.union("Bob", "Charlie")  # Now Alice, Bob, Charlie, David are together

# print(f"Alice and Eve connected? {ds.connected('Alice', 'Eve')}")  # False
# print(f"Alice and David connected? {ds.connected('Alice', 'David')}")  # True
# print(f"Number of sets: {ds.get_number_of_sets()}")  # 2

# # Get members of Alice's group
# members = ds.get_set_members("Alice")
# print(f"Alice's group members: {members}")

# # Example 2: Using with custom objects
# class Node:
#     def __init__(self, id):
#         self.id = id
#     def __repr__(self):
#         return f"Node({self.id})"

# nodes = [Node(i) for i in range(5)]
# ds2 = DisjointSet()

# for node in nodes:
#     ds2.make_set(node)

# ds2.union(nodes[0], nodes[2])
# ds2.union(nodes[1], nodes[3])

# print(f"Node(0) and Node(2) connected? {ds2.connected(nodes[0], nodes[2])}")

