# 05. Binary Search

## Core Idea
Binary search works whenever you can ask a yes/no question about the middle of a range and the answer tells you which half to throw away. On a sorted array the question is "is a[mid] < target?". More generally, any **monotonic predicate** (false…false, true…true) can be searched for its first true: the array index, the eating speed, the square root, the partition point. Each step halves the range, so it's O(log n) checks. Almost every bug is in the boundaries, so pick one template and stick to it.

## When to Use
- The input is sorted (or rotated sorted) and you need O(log n) (0704, 0033, 0153).
- "Find the first / last position where…" (lower and upper bound: 0035, 0034).
- "Minimum k such that it's feasible" / "maximum k such that it still works" (binary search on the answer: 0875, 0069).
- A 2-D structure that flattens to a sorted sequence (0074).
- Sorted versions per key with "latest ≤ t" lookups (0981).
- The answer is a split point between two sorted arrays (0004).
- Local structure tells you a direction, even without sorting (0162).

## Templates

### Exact match, inclusive [lo, hi]
```cpp
int lo = 0, hi = n - 1;
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (a[mid] == x) return mid;
    if (a[mid] < x) lo = mid + 1; else hi = mid - 1;
}
return -1;
```
```python
lo, hi = 0, len(a) - 1
while lo <= hi:
    mid = (lo + hi) // 2
    if a[mid] == x:
        return mid
    if a[mid] < x:
        lo = mid + 1
    else:
        hi = mid - 1
return -1
```
```go
lo, hi := 0, len(a)-1
for lo <= hi {
	mid := lo + (hi-lo)/2
	if a[mid] == x {
		return mid
	}
	if a[mid] < x {
		lo = mid + 1
	} else {
		hi = mid - 1
	}
}
return -1
```

### First index where a predicate is true, half-open [lo, hi)
Lower bound is `ok(i) = a[i] >= x`; upper bound is `a[i] > x`; on the answer, `ok(k) = feasible(k)`.
```cpp
int lo = 0, hi = n;                        // answer can be n ("none")
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (ok(mid)) hi = mid; else lo = mid + 1;
}
return lo;
```
```python
lo, hi = 0, n
while lo < hi:
    mid = (lo + hi) // 2
    if ok(mid):
        hi = mid
    else:
        lo = mid + 1
return lo
```
```go
lo, hi := 0, n
for lo < hi {
	mid := lo + (hi-lo)/2
	if ok(mid) {
		hi = mid
	} else {
		lo = mid + 1
	}
}
return lo // same as sort.Search(n, ok)
```

### Last value where a predicate holds (record-and-continue)
```cpp
long long lo = 0, hi = x, ans = 0;
while (lo <= hi) {
    long long mid = lo + (hi - lo) / 2;
    if (good(mid)) { ans = mid; lo = mid + 1; } else hi = mid - 1;
}
```
```python
lo, hi, ans = 0, x, 0
while lo <= hi:
    mid = (lo + hi) // 2
    if good(mid):
        ans, lo = mid, mid + 1
    else:
        hi = mid - 1
```
```go
lo, hi, ans := 0, x, 0
for lo <= hi {
	mid := lo + (hi-lo)/2
	if good(mid) {
		ans, lo = mid, mid+1
	} else {
		hi = mid - 1
	}
}
```

## Common Variations
- **Lower / upper bound:** first ≥ x and first > x; the count of x is their difference (0035, 0034).
- **Binary search on the answer:** search the value space [lo, hi] with a feasibility check, O(n log range) (0875, 0069).
- **Rotated arrays:** compare mid with the right end to find the drop (0153), or decide which half is sorted (0033).
- **Flattened 2-D:** index k ↔ (k / cols, k % cols) (0074).
- **Search on a neighbour comparison:** move toward the uphill side (0162).
- **Search on a partition:** choose how many come from one array; check cross conditions (0004).
- **Per-key sorted lists:** append keeps order when timestamps increase; search with upper bound - 1 (0981).
- **First true of an expensive predicate:** minimise API calls with the `lo < hi` template (0278); a predicate can mix index and value, e.g. `c[i] ≥ n − i` (0275).
- **Minimise the maximum:** search the cap over [max, sum] and count pieces greedily (0410, 1011); sum of ceilings for divisors (1283).
- **Duplicates in rotated arrays:** when lo, mid and hi are equal, shrink the ends (0081) or do `hi−−` (0154). The worst case becomes O(n).
- **Unknown size:** double hi until it passes the target, then search (0702).
- **k-th smallest of an implicit set:** binary search the value and count how many are ≤ it (0719).
- **Not really binary search:** a sorted-rows-and-columns matrix uses a staircase walk from the top-right (0240).

## ⚠️ Pitfalls
- **Mixing templates:** `lo <= hi` pairs with `hi = mid - 1`; `lo < hi` pairs with `hi = mid`. Mixing them gives infinite loops or skipped candidates.
- **Midpoint overflow** in C++/Java: `lo + (hi - lo) / 2`. Squares and sums of large values need `long long`.
- **Wrong initial hi:** use n (not n - 1) when "not found / insert at end" is a valid answer.
- **Rounding direction:** with `lo = mid` (not `mid + 1`) you need an upper midpoint `lo + (hi - lo + 1) / 2`, or the loop stalls.
- **`size_t` in C++:** `hi = mid - 1` with `mid == 0` wraps around. Keep indices `int`.
- **Python `bisect`** on a list of tuples compares whole tuples; use parallel lists or `key=` (3.10+).

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0035 | [Search Insert Position](0035-search-insert-position/) | Easy | Lower bound | ✅ |
| 0069 | [Sqrt(x)](0069-sqrtx/) | Easy | Binary search on answer | ✅ |
| 0278 | [First Bad Version](0278-first-bad-version/) | Easy | First true of a predicate | ✅ |
| 0367 | [Valid Perfect Square](0367-valid-perfect-square/) | Easy | Binary search on the root | ✅ |
| 0704 | [Binary Search](0704-binary-search/) | Easy | Classic binary search | ✅ |
| 0033 | [Search in Rotated Sorted Array](0033-search-in-rotated-sorted-array/) | Medium | Find the sorted half | ✅ |
| 0034 | [Find First and Last Position of Element in Sorted Array](0034-find-first-and-last-position-of-element-in-sorted-array/) | Medium | Lower & upper bound | ✅ |
| 0074 | [Search a 2D Matrix](0074-search-a-2d-matrix/) | Medium | Treat as flat sorted array | ✅ |
| 0081 | [Search in Rotated Sorted Array II](0081-search-in-rotated-sorted-array-ii/) | Medium | Sorted half + shrink ends on ties | ✅ |
| 0153 | [Find Minimum in Rotated Sorted Array](0153-find-minimum-in-rotated-sorted-array/) | Medium | Compare mid with right | ✅ |
| 0162 | [Find Peak Element](0162-find-peak-element/) | Medium | Binary search on slope | ✅ |
| 0240 | [Search a 2D Matrix II](0240-search-a-2d-matrix-ii/) | Medium | Staircase from top-right | ✅ |
| 0275 | [H-Index II](0275-h-index-ii/) | Medium | First i with c[i] ≥ n − i | ✅ |
| 0702 | [Search in a Sorted Array of Unknown Size](0702-search-in-a-sorted-array-of-unknown-size/) | Medium | Exponential bound + binary search | ✅ |
| 0852 | [Peak Index in a Mountain Array](0852-peak-index-in-a-mountain-array/) | Medium | Binary search on slope | ✅ |
| 0875 | [Koko Eating Bananas](0875-koko-eating-bananas/) | Medium | Binary search on answer | ✅ |
| 0981 | [Time Based Key-Value Store](0981-time-based-key-value-store/) | Medium | Hashmap + binary search on time | ✅ |
| 1011 | [Capacity To Ship Packages Within D Days](1011-capacity-to-ship-packages-within-d-days/) | Medium | Binary search on answer + greedy days | ✅ |
| 1283 | [Find the Smallest Divisor Given a Threshold](1283-find-the-smallest-divisor-given-a-threshold/) | Medium | Binary search on answer (sum of ceilings) | ✅ |
| 0004 | [Median of Two Sorted Arrays](0004-median-of-two-sorted-arrays/) | Hard | Binary search on partition | ✅ |
| 0154 | [Find Minimum in Rotated Sorted Array II](0154-find-minimum-in-rotated-sorted-array-ii/) | Hard | Compare mid with right, hi−− on ties | ✅ |
| 0410 | [Split Array Largest Sum](0410-split-array-largest-sum/) | Hard | Binary search on answer + greedy pieces | ✅ |
| 0719 | [Find K-th Smallest Pair Distance](0719-find-k-th-smallest-pair-distance/) | Hard | Binary search on value + two-pointer count | ✅ |
