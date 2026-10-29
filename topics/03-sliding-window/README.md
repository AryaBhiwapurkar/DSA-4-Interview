# 03. Sliding Window

## Core Idea
A window is a contiguous range [l, r] that moves left to right. Instead of recomputing each subarray/substring from scratch, update a running state (sum, counts, set, deque) as r adds an element and l removes one. Each index enters and leaves the window at most once, so the whole scan is O(n). Two flavours: **fixed size** (r - l + 1 == k, slide both together) and **variable size** (grow r, shrink l while the window is invalid, or while it's still valid when looking for the shortest).

## When to Use
- "Longest / shortest / count of **contiguous** subarray or substring" with a constraint.
- "At most k distinct / at most k replacements / no repeats".
- "Window of size k": max, average, anagram/permutation check, duplicates within distance k.
- "Minimum window containing all of X".
- Running best-so-far over a prefix (e.g. min price before today).
- **Not** for non-contiguous picks (that's DP/backtracking), and the variable window needs monotonicity: e.g. sums only work with non-negative numbers.

## Templates

### Variable window, longest valid
```cpp
int l = 0, best = 0;
for (int r = 0; r < n; r++) {
    add(a[r]);
    while (!valid()) remove(a[l++]);
    best = max(best, r - l + 1);
}
```
```python
l = best = 0
for r, x in enumerate(a):
    add(x)
    while not valid():
        remove(a[l])
        l += 1
    best = max(best, r - l + 1)
```
```go
l, best := 0, 0
for r, x := range a {
	add(x)
	for !valid() {
		remove(a[l])
		l++
	}
	best = max(best, r-l+1)
}
```

### Variable window, shortest valid
```cpp
int l = 0, best = INT_MAX;
for (int r = 0; r < n; r++) {
    add(a[r]);
    while (valid()) { best = min(best, r - l + 1); remove(a[l++]); }
}
return best == INT_MAX ? 0 : best;
```
```python
l, best = 0, float("inf")
for r, x in enumerate(a):
    add(x)
    while valid():
        best = min(best, r - l + 1)
        remove(a[l])
        l += 1
return 0 if best == float("inf") else best
```
```go
l, best := 0, math.MaxInt
for r, x := range a {
	add(x)
	for valid() {
		best = min(best, r-l+1)
		remove(a[l])
		l++
	}
}
if best == math.MaxInt {
	best = 0
}
```

### Fixed window of size k
```cpp
for (int r = 0; r < n; r++) {
    add(a[r]);
    if (r >= k) remove(a[r - k]);
    if (r >= k - 1) record();          // window is a[r-k+1..r]
}
```
```python
for r, x in enumerate(a):
    add(x)
    if r >= k:
        remove(a[r - k])
    if r >= k - 1:
        record()
```
```go
for r, x := range a {
	add(x)
	if r >= k {
		remove(a[r-k])
	}
	if r >= k-1 {
		record()
	}
}
```

### Monotonic deque (window max)
```cpp
deque<int> dq;                                     // indices, values decreasing
for (int i = 0; i < n; i++) {
    if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
    while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
    dq.push_back(i);
    if (i >= k - 1) out.push_back(a[dq.front()]);
}
```
```python
dq = deque()
for i, x in enumerate(a):
    if dq and dq[0] <= i - k:
        dq.popleft()
    while dq and a[dq[-1]] <= x:
        dq.pop()
    dq.append(i)
    if i >= k - 1:
        out.append(a[dq[0]])
```
```go
dq := []int{}
for i, x := range a {
	if len(dq) > 0 && dq[0] <= i-k {
		dq = dq[1:]
	}
	for len(dq) > 0 && a[dq[len(dq)-1]] <= x {
		dq = dq[:len(dq)-1]
	}
	dq = append(dq, i)
	if i >= k-1 {
		out = append(out, a[dq[0]])
	}
}
```

## Common Variations
- **Validity via counts:** 26/128 array for letters, hashmap otherwise (0567, 0076).
- **have/need counter:** O(1) validity check instead of comparing whole count arrays (0076).
- **Stale max frequency:** `len - maxFreq ≤ k` with a never-decreasing maxFreq (0424).
- **Jump instead of shrink:** last-seen index lets l jump in one step; use `max(l, last+1)` (0003).
- **Window of words:** tokenize by fixed word length and run one window per offset (0030).
- **Running min/max as a degenerate window:** best trade so far (0121).
- **Window + set for "within distance k"** (0219).

## ⚠️ Pitfalls
- **Negative numbers break sum windows:** shrinking may increase the sum; use prefix sums (+ hashmap/deque) instead.
- **Record at the right time:** longest → after shrinking to valid; shortest → inside the shrink loop while valid.
- **Off-by-one on the fixed window:** remove `a[r - k]` when adding `a[r]`; first full window at `r = k - 1`.
- **Storing values instead of indices** in a deque: you can't expire them.
- **`if` vs `while` when shrinking:** most templates need `while`; the 0424 trick is the deliberate exception.
- **Slicing substrings inside the loop** costs O(len) each time; track (start, length) and slice once.

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0121 | [Best Time to Buy and Sell Stock](0121-best-time-to-buy-and-sell-stock/) | Easy | Running min | ✅ |
| 0219 | [Contains Duplicate II](0219-contains-duplicate-ii/) | Easy | Fixed window + set | ✅ |
| 0003 | [Longest Substring Without Repeating Characters](0003-longest-substring-without-repeating-characters/) | Medium | Variable window + last-seen map | ✅ |
| 0209 | [Minimum Size Subarray Sum](0209-minimum-size-subarray-sum/) | Medium | Variable window, shrink while valid | ✅ |
| 0424 | [Longest Repeating Character Replacement](0424-longest-repeating-character-replacement/) | Medium | Variable window + max freq | ✅ |
| 0567 | [Permutation in String](0567-permutation-in-string/) | Medium | Fixed window + counts | ✅ |
| 0030 | [Substring with Concatenation of All Words](0030-substring-with-concatenation-of-all-words/) | Hard | Fixed window per offset + counts | ✅ |
| 0076 | [Minimum Window Substring](0076-minimum-window-substring/) | Hard | Variable window + need/have | ✅ |
| 0239 | [Sliding Window Maximum](0239-sliding-window-maximum/) | Hard | Monotonic deque | ✅ |
