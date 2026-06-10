def activity_selector_unsorted(start, finish):
    activities = []

    for i in range(len(start)):
        activities.append((i, start[i], finish[i]))

    activities.sort(key=lambda x: x[2])

    selected = []
    last_finish_time = 0

    for index, s, f in activities:
        if s >= last_finish_time:
            selected.append(index)
            last_finish_time = f

    return selected

start =  [1, 3, 0, 5, 8, 5]
finish = [2, 4, 6, 7, 9, 9]

selected = activity_selector_unsorted(start, finish)

print("Selected activity indexes:", selected)
