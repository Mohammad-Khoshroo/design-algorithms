def fractional_knapsack(values, weights, W):
    n = len(values)

    items = []
    for i in range(n):
        ratio = weights[i] / values[i]
        items.append((i, values[i], weights[i], ratio))

    items.sort(key=lambda x: x[3])

    total_value = 0
    selected_items = []

    remaining_capacity = W

    for index, value, weight, ratio in items:
        if remaining_capacity == 0:
            break

        if weight <= remaining_capacity:
            total_value += value
            remaining_capacity -= weight
            selected_items.append((index, 1))
        else:
            fraction = remaining_capacity / weight
            total_value += value * fraction
            selected_items.append((index, fraction))
            remaining_capacity = 0

    return total_value, selected_items


values = [60, 100, 120]
weights = [10, 20, 30]
W = 50

max_value, selected = fractional_knapsack(values, weights, W)

print("Max value:", max_value)
print("Selected items:", selected)
