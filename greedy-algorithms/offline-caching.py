from collections import defaultdict, deque

def offline_caching(capacity, requests):
    
    future_occurrences = defaultdict(deque)
    for index, item in enumerate(requests):
        future_occurrences[item].append(index)
    
    cache = set()
    cache_misses = 0
    steps_log = []
    
    for current_step, item in enumerate(requests):
        if future_occurrences[item]:
            future_occurrences[item].popleft()
            
        if item in cache:
            steps_log.append(f"Request: {item} | Cache: {list(cache)} | Result: HIT")
            continue
        
        cache_misses += 1
        
        if len(cache) < capacity:
            cache.add(item)
        else:
            farthest_item = None
            farthest_distance = -1
            
            for cached_item in cache:
                if not future_occurrences[cached_item]:
                    farthest_item = cached_item
                    break
                
                next_use = future_occurrences[cached_item][0]
                if next_use > farthest_distance:
                    farthest_distance = next_use
                    farthest_item = cached_item
            
            cache.remove(farthest_item)
            cache.add(item)
            
        steps_log.append(f"Request: {item} | Cache: {list(cache)} | Result: MISS")
        
    return cache_misses, steps_log

capacity = 4
requests = ['A', 'B', 'C', 'A', 'B', 'D', 'A']

total_misses, logs = offline_caching(capacity, requests)

print(f"Total Cache Misses: {total_misses}\n")
print("Execution Steps:")
for log in logs:
    print(log)
