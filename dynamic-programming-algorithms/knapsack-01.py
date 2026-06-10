def knapsack(v, w, W):
    n = len(values)
    A = [[0 for _ in range(W + 1)] for _ in range(n + 1)]

    for j in range(W + 1):
        A[0][j] = 0

    for i in range(1, n + 1):
        for j in range(W + 1):
            A[i][j] = A[i - 1][j]
            if w[i - 1] <= j and A[i - 1][j - w[i - 1]] + v[i - 1] > A[i - 1][j]:
                A[i][j] = v[i - 1] + A[i - 1][j - w[i - 1]]

    return A[n][W]


def knapsack_with_items(values, weights, W):
    n = len(values)
    A = [[0 for _ in range(W + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(W + 1):
            A[i][j] = A[i - 1][j]

            if weights[i - 1] <= j:
                new_value = values[i - 1] + A[i - 1][j - weights[i - 1]]
                if new_value > A[i][j]:
                    A[i][j] = new_value

    selected_items = []
    j = W

    for i in range(n, 0, -1):
        if A[i][j] != A[i - 1][j]:
            selected_items.append(i - 1)
            j -= weights[i - 1]

    selected_items.reverse()

    return A[n][W], selected_items


def knapsack_optimized(values, weights, W):
    dp = [0 for _ in range(W + 1)]

    for i in range(len(values)):
        for j in range(W, weights[i] - 1, -1):
            dp[j] = max(dp[j], values[i] + dp[j - weights[i]])

    return dp[W]


values = [60, 100, 120]
weights = [10, 20, 30]
W = 50

max_value, items = knapsack_with_items(values, weights, W)

print("Max value:", max_value)
print("Selected item indexes:", items)
print("Selected values:", [values[i] for i in items])
print("Selected weights:", [weights[i] for i in items])
