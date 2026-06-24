def coin_change_dp(coins, amount):
    dp = [amount + 1] * (amount + 1)
    
    dp[0] = 0
    
    for i in range(1, amount + 1):
        for coin in coins:
            if i >= coin:
                dp[i] = min(dp[i], dp[i - coin] + 1)
                
    if dp[amount] > amount:
        return -1
        
    return dp[amount]

coins = [1, 5, 6, 10]
amount = 12

min_coins = coin_change_dp(coins, amount)
print(f"Minimum coins needed: {min_coins}") # Output: 2
