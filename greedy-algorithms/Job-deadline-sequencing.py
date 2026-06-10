def job_sequencing(jobs):

    jobs = sorted(jobs, key=lambda x: x[2], reverse=True)

    max_deadline = max(job[1] for job in jobs)

    slots = [None] * (max_deadline + 1)

    total_profit = 0
    scheduled_jobs = []

    for job_id, deadline, profit in jobs:
        for t in range(deadline, 0, -1):
            if t <= max_deadline and slots[t] is None:
                slots[t] = job_id
                total_profit += profit
                scheduled_jobs.append((job_id, t))
                break
    scheduled_jobs.sort(key=lambda x: x[1])

    return scheduled_jobs, total_profit


input_jobs = [
    ("J1", 2, 100),
    ("J2", 1, 19),
    ("J3", 2, 27),
    ("J4", 1, 25),
    ("J5", 3, 15),
]

schedule, max_profit = job_sequencing(input_jobs)

print("Scheduled Jobs (Job, Slot):", schedule)
print("Total Profit:", max_profit)
