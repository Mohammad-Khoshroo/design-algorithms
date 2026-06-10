def is_canonical(coins):
    coins = sorted(coins)
    n = len(coins)
    
    def greedy_count(amount, available_coins):
        count = 0
        for c in reversed(available_coins):
            if amount == 0:
                break
            count += amount // c
            amount %= c
        return count

    for i in range(n - 1):
        for j in range(i + 1, n):
            target = coins[j] - 1
            
            sub_coins = coins[:i+1]
            q_i = target // coins[i]
            
            w = target - (q_i * coins[i]) + coins[i]
            expected_count = greedy_count(target - (q_i * coins[i]), sub_coins[:-1]) + 1
            
            actual_greedy_count = greedy_count(w, coins)
            
            if actual_greedy_count > expected_count:
                return False
                
    return True

us_coins = [1, 5, 10, 25]
print(f"US coins {us_coins} canonical? : {is_canonical(us_coins)}")

non_canonical_coins = [1, 5, 6, 10]
print(f"Coins {non_canonical_coins} canonical? : {is_canonical(non_canonical_coins)}")
