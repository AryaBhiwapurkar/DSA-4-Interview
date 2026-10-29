# 02. Two Pointers

## Core Idea
Use two indices that move through the data in a coordinated way so each step rules out work you'd otherwise repeat. Three shapes cover almost everything: **converging** (one at each end, move inward based on a comparison), **read/write** (a fast reader and a slow writer compacting in place), and **two sequences** (one pointer per array/string, advancing like a merge). Each pointer only moves forward, so the scan is O(n) with O(1) extra space.

## When to Use
- Input is **sorted** (or you can sort it) and you need a pair/triplet with a target sum.
- "In place", "O(1) extra space", "remove/dedupe and return the new length".
- Palindrome checks, reversing, comparing from both ends.
- Merging two sorted sequences; checking if one sequence is a subsequence of another.
- "Maximize area/water between two boundaries".

## Templates

### Converging pointers (sorted pair sum)
```cpp
int l = 0, r = a.size() - 1;
while (l < r) {
    int s = a[l] + a[r];
    if (s == target) return {l, r};
    if (s < target) l++; else r--;
}
```
```python
l, r = 0, len(a) - 1
while l < r:
    s = a[l] + a[r]
    if s == target:
        return [l, r]
    if s < target:
        l += 1
    else:
        r -= 1
```
```go
l, r := 0, len(a)-1
for l < r {
	s := a[l] + a[r]
	if s == target {
		return []int{l, r}
	}
	if s < target {
		l++
	} else {
		r--
	}
}
```

### Read/write (in-place filter)
```cpp
int k = 0;
for (int x : nums) if (keep(x)) nums[k++] = x;   // nums[0..k) is the result
```
```python
k = 0
for x in nums:
    if keep(x):
        nums[k] = x
        k += 1
```
```go
k := 0
for _, x := range nums {
	if keep(x) {
		nums[k] = x
		k++
	}
}
```

### Two sequences (merge / subsequence)
```cpp
int i = 0, j = 0;
while (i < a.size() && j < b.size()) {
    if (a[i] <= b[j]) out.push_back(a[i++]); else out.push_back(b[j++]);
}
// append leftovers of a and b
```
```python
i = j = 0
while i < len(a) and j < len(b):
    if a[i] <= b[j]:
        out.append(a[i]); i += 1
    else:
        out.append(b[j]); j += 1
out += a[i:] + b[j:]
```
```go
i, j := 0, 0
for i < len(a) && j < len(b) {
	if a[i] <= b[j] {
		out = append(out, a[i])
		i++
	} else {
		out = append(out, b[j])
		j++
	}
}
out = append(append(out, a[i:]...), b[j:]...)
```

## Common Variations
- **Fix one, two-pointer the rest:** 3Sum / 4Sum after sorting (0015). Skip duplicates by comparing with the previous value.
- **Move the bottleneck:** shorter wall (0011) or smaller running max (0042).
- **Fill from the back:** when the free space is at the end (0088).
- **Keep at most m copies:** compare with `nums[k-m]` (0026, 0080).
- **Skip junk while converging:** non-alphanumerics in palindromes (0125).
- **Swap with end:** O(1) removal when order doesn't matter (0027).

## ⚠️ Pitfalls
- **Sortedness is required** for converging pair sums; sorting loses original indices unless you keep (value, index) pairs.
- **Inner skip loops** must re-check `l < r` or they run past each other.
- **Duplicate skipping:** compare with the *previous* element (`a[i] == a[i-1]`), not the next, or valid answers get skipped.
- **Compare with the output, not the input,** in read/write (slots behind the reader may already be overwritten).
- **C++ `size_t` underflow:** `a.size() - 1` on an empty vector wraps; use `int`.
- **Make sure every loop iteration moves at least one pointer** (e.g. after recording a 3Sum hit, move both).

## Problems

| # | Problem | Difficulty | Pattern | Status |
|---|---------|------------|---------|--------|
| 0026 | [Remove Duplicates from Sorted Array](0026-remove-duplicates-from-sorted-array/) | Easy | Read/write pointers | ✅ |
| 0027 | [Remove Element](0027-remove-element/) | Easy | Read/write pointers | ✅ |
| 0088 | [Merge Sorted Array](0088-merge-sorted-array/) | Easy | Merge from the back | ✅ |
| 0125 | [Valid Palindrome](0125-valid-palindrome/) | Easy | Converging pointers | ✅ |
| 0392 | [Is Subsequence](0392-is-subsequence/) | Easy | Two pointers on two strings | ✅ |
| 0011 | [Container With Most Water](0011-container-with-most-water/) | Medium | Converging, move shorter side | ✅ |
| 0015 | [3Sum](0015-3sum/) | Medium | Sort + fix one + two pointers | ✅ |
| 0080 | [Remove Duplicates from Sorted Array II](0080-remove-duplicates-from-sorted-array-ii/) | Medium | Read/write, compare k back | ✅ |
| 0167 | [Two Sum II - Input Array Is Sorted](0167-two-sum-ii-input-array-is-sorted/) | Medium | Converging pointers on sorted | ✅ |
| 0042 | [Trapping Rain Water](0042-trapping-rain-water/) | Hard | Two pointers with running max | ✅ |
