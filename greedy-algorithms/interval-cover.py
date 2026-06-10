def interval_cover(points, L):
    if not points:
        return 0, []
    
    sorted_points = sorted(points)
    
    intervals = []
    start_of_current_interval = sorted_points[0]
    intervals.append((start_of_current_interval, start_of_current_interval + L))
    
    for point in sorted_points[1:]:
        end_of_current_interval = start_of_current_interval + L
        
        if point > end_of_current_interval:
            start_of_current_interval = point
            intervals.append((start_of_current_interval, start_of_current_interval + L))
            
    return len(intervals), intervals

points = [1, 9, 4, 5, 6]
L = 4

num_intervals, cover_intervals = interval_cover(points, L)

print(f"Points (Sorted): {sorted(points)}")
print(f"Interval Length (L): {L}")
print(f"Minimum Intervals Needed: {num_intervals}")
print("Intervals:")
for i, interval in enumerate(cover_intervals, 1):
    print(f"  Interval {i}: {interval}")
