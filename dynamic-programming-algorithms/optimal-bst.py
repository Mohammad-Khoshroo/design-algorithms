def optimal_bst(p, q, n):
    e = [[0.0 for _ in range(n + 1)] for _ in range(n + 2)]
    w = [[0.0 for _ in range(n + 1)] for _ in range(n + 2)]
    root = [[0 for _ in range(n + 1)] for _ in range(n + 1)]

    for i in range(1, n + 2):
        e[i][i - 1] = q[i - 1]
        w[i][i - 1] = q[i - 1]

    for l in range(1, n + 1):
        for i in range(1, n - l + 2):
            j = i + l - 1
            e[i][j] = float('inf')
            w[i][j] = round(w[i][j - 1] + p[j] + q[j], 2)
            
            for r in range(i, j + 1):
                t = e[i][r - 1] + e[r + 1][j] + w[i][j]
                if t < e[i][j]:
                    e[i][j] = round(t, 2)
                    root[i][j] = r

    return e, w, root

n = 7
p = [0.00, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14]
q = [0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05]

e, w, root = optimal_bst(p, q, n)

print("e cost-table")
for i in range(1, n + 2):
    print([f"{val:.2f}" if val != float('inf') else "inf" for val in e[i][:n+1]])

print("\nw")
for i in range(1, n + 2):
    print([f"{val:.2f}" for val in w[i][:n+1]])

print("\nroot table")
for i in range(1, n + 1):
    print(root[i][1:n+1])
