import sys

def matrix_chain_order(p):
    n = len(p) - 1
    m = [[0 for _ in range(n + 1)] for _ in range(n + 1)]
    s = [[0 for _ in range(n + 1)] for _ in range(n + 1)]

    for L in range(2, n + 1):
        for i in range(1, n - L + 2):
            j = i + L - 1
            m[i][j] = sys.maxsize
            for k in range(i, j):
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k
                    
    return m, s

def print_optimal_parens(s, i, j):
    if i == j:
        return f"A{i}"
    else:
        left = print_optimal_parens(s, i, s[i][j])
        right = print_optimal_parens(s, s[i][j] + 1, j)
        return f"({left}{right})"

p = [5, 10, 3, 12, 5, 50, 6]
n = len(p) - 1

m, s = matrix_chain_order(p)

print(f"(m[1][{n}]): {m[1][n]}")
print(f"{print_optimal_parens(s, 1, n)}")
print("-" * 40)

print("m:")
for i in range(1, n + 1):
    row = []
    for j in range(1, n + 1):
        if i <= j:
            row.append(f"{m[i][j]:<6}")
        else:
            row.append("      ")
    print(" ".join(row))

print("\nk:")
for i in range(1, n):
    row = []
    for j in range(2, n + 1):
        if i < j:
            row.append(f"{s[i][j]:<3}")
        else:
            row.append("   ")
    print(" ".join(row))
