def print_lcs_table(X, Y):
    m = len(X)
    n = len(Y)
    
    c = [[0] * (n + 1) for _ in range(m + 1)]
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if X[i - 1] == Y[j - 1]:
                c[i][j] = c[i - 1][j - 1] + 1
            else:
                c[i][j] = max(c[i - 1][j], c[i][j - 1])
                
    header = "      ∅"
    for y in Y:
        header += f"  {y}"
    print(header)
    
    for i in range(m + 1):
        row_label = "∅" if i == 0 else str(X[i - 1])
        row_str = f"{row_label} |"
        for j in range(n + 1):
            row_str += f"{c[i][j]:>3}"
        print(row_str)

X = [1, 0, 0, 1, 0, 1, 0, 1]
Y = [0, 1, 0, 1, 1, 0, 1, 1, 0]

print_lcs_table(X, Y)
