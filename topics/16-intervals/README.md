# 16. Intervals

## Core Idea
Almost every interval problem starts with a **sort**, and the choice of key decides the algorithm. Sort by **start** to merge or insert (overlaps become neighbours). Sort by **end** to keep the most disjoint intervals or to stab them with the fewest points (the earliest end leaves the most room). For "how many at once" questions, sweep over time with +1/−1 events or a min-heap of end times. Decide up front whether touching intervals ([1,2], [2,3]) overlap; that single `<` vs `<=` is the most common bug.

## When to Use
- Combine overlapping ranges: sort by start, extend the last one (0056).
- Insert into a sorted disjoint list: before / overlap / after phases (0057).
- Any two overlap? Sort, compare neighbours (0252).
- Max simultaneous intervals / rooms: min-heap of ends or a sweep line (0253).
- Remove fewest to make disjoint, or fewest points to stab all: sort by end, greedy (0435, 0452).
- Many point queries over intervals: sort queries offline, sweep with a heap (1851).
- Compress a sorted list into runs: scan while next == cur + 1 (0228).

## Templates

### Merge (sort by start)
```cpp
sort(iv.begin(), iv.end());
vector<vector<int>> res;
for (auto& x : iv)
    if (!res.empty() && x[0] <= res.back()[1]) res.back()[1] = max(res.back()[1], x[1]);
    else res.push_back(x);
```
```python
res = []
for s, e in sorted(intervals):
    if res and s <= res[-1][1]:
        res[-1][1] = max(res[-1][1], e)
    else:
        res.append([s, e])
```

### Greedy by end (max disjoint / min arrows)
```python
count, end = 0, float("-inf")
for s, e in sorted(intervals, key=lambda iv: iv[1]):
    if s >= end:              # 0452 uses s > end: touching balloons share an arrow
        count += 1
        end = e
```

### Rooms: min-heap of end times
```python
ends = []
for s, e in sorted(intervals):
    if ends and ends[0] <= s:
        heapq.heapreplace(ends, e)
    else:
        heapq.heappush(ends, e)
return len(ends)
```

### Offline queries + heap
```python
i = 0                                             # pointer into intervals sorted by left
for q, qi in sorted((q, k) for k, q in enumerate(queries)):
    while i < n and iv[i][0] <= q:
        heappush(h, (iv[i][1] - iv[i][0] + 1, iv[i][1])); i += 1
    while h and h[0][1] < q: heappop(h)
    res[qi] = h[0][0] if h else -1
```

## Common Variations
- **Touching counts as overlap?** 0056/0057 merge touching intervals; 0252/0253/0435 treat them as fine; 0452 lets one arrow hit both.
- **Sweep line with weights:** passengers, flowers in bloom, calendar bookings.
- **Intervals hidden in data:** first/last occurrence of letters (0763).
- **Sorted input given:** use it for O(n) (0057) instead of re-sorting.

## ⚠️ Pitfalls
- **`<` vs `<=`** for touching intervals: read the statement carefully.
- **Nested intervals:** merging must take `max(end)`, not the new end.
- **Comparator overflow:** `a[1] - b[1]` breaks near ±2³¹ (0452); compare with `<`.
- **Sentinels:** coordinates can be negative or reach INT_MIN; seed with the first interval.
- **C++ priority_queue is a max-heap** by default.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0228 | [Summary Ranges](0228-summary-ranges/) | Easy | Linear scan of runs | ✅ |
| 0252 | [Meeting Rooms](0252-meeting-rooms/) | Easy | Sort + check overlap | ✅ |
| 0056 | [Merge Intervals](0056-merge-intervals/) | Medium | Sort by start + merge | ✅ |
| 0057 | [Insert Interval](0057-insert-interval/) | Medium | Merge on the fly | ✅ |
| 0253 | [Meeting Rooms II](0253-meeting-rooms-ii/) | Medium | Sorted starts/ends or min-heap | ✅ |
| 0435 | [Non-overlapping Intervals](0435-non-overlapping-intervals/) | Medium | Sort by end, greedy | ✅ |
| 0452 | [Minimum Number of Arrows to Burst Balloons](0452-minimum-number-of-arrows-to-burst-balloons/) | Medium | Sort by end, greedy | ✅ |
| 1851 | [Minimum Interval to Include Each Query](1851-minimum-interval-to-include-each-query/) | Hard | Sort queries + min-heap | ✅ |
