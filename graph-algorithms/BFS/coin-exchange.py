from collections import deque

def coin_change_bfs(coins, amount):
    if amount == 0:
        return 0
        
    queue = deque([(amount, 0)])
    
    visited = set([amount])
    
    while queue:
        curr_amount, num_coins = queue.popleft()
        
        for coin in coins:
            next_amount = curr_amount - coin
            
            if next_amount == 0:
                return num_coins + 1
                
            if next_amount > 0 and next_amount not in visited:
                visited.add(next_amount)
                queue.append((next_amount, num_coins + 1))
                
    return -1

coins = [1, 5, 6, 10]
amount = 12

min_coins = coin_change_bfs(coins, amount)
print(f"Minimum coins needed: {min_coins}") # Output: 2
