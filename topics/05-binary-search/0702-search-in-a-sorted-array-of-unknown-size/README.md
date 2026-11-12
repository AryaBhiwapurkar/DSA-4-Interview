---
number: 702
title: Search in a Sorted Array of Unknown Size
difficulty: Medium
topic: Binary Search
pattern: Exponential search: double the bound, then binary search
link: https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/
lists: [Interview Extras]
followup_of: ["0704 Binary Search"]
related: ["0704 Binary Search", "0278 First Bad Version", "0035 Search Insert Position"]
---

# 0702. Search in a Sorted Array of Unknown Size

## ⚡ 30-Second Summary
**Pattern:** Exponential (galloping) search
**Key insight:** You don't know n, but reads past the end return 2³¹ − 1, which is bigger than any real value. So the array behaves like a sorted array padded with +∞. Double `hi` (1, 2, 4, …) until `get(hi) ≥ target`. The target, if present, is now in [lo, hi]; binary search there. Both phases take O(log k), where k is the target's index.
**Go-to:** Double the bound, then binary search, O(log k) time, O(1) space

## Problem
A sorted array of distinct integers can only be read through `reader.get(i)`. Reading past the end returns 2³¹ − 1. Return the index of target, or −1, in O(log n) time. (Premium problem.) [LeetCode](https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/)

**Examples:**
```
Input:  secret = [-1,0,3,5,9,12], target = 9
Output: 4
Why:    9 is at index 4.

Input:  secret = [-1,0,3,5,9,12], target = 2
Output: -1
Why:    2 would sit between 0 and 3; it isn't there.
```

**Constraints:**
- 1 ≤ length ≤ 10⁴; values in [−10⁴, 10⁴], distinct and sorted; target in the same range.

## Hints
<details><summary>Hint 1</summary>
What does get(i) return past the end, and how does that compare to any real value?
</details>
<details><summary>Hint 2</summary>
The out-of-range reads act like +∞, so the sequence stays sorted. You only need some hi with get(hi) ≥ target. How fast can you find one?
</details>
<details><summary>Hint 3</summary>
Start with lo = 0, hi = 1. While get(hi) < target: lo = hi, hi *= 2. Then do a normal binary search on [lo, hi]; out-of-range mids just compare as "too big".
</details>

## Clarifying Questions
- Values are distinct? (Yes.)
- What exactly does an out-of-range read return? (2³¹ − 1, larger than any value.)
- Is target guaranteed in the value range? (Yes, ≤ 10⁴, so it never equals the sentinel.)

## Example Walkthrough
target = 9: get(1) = 0 < 9 → [1, 2]; get(2) = 3 < 9 → [2, 4]; get(4) = 9 ≥ 9 → stop. Binary search [2, 4]: mid = 3 → 5 < 9 → lo = 4; mid = 4 → 9 → return 4.

## Approaches

### 1. Linear Scan: O(k) time, O(1) space
Read get(0), get(1), … until the value is ≥ target. Simple, but linear.

### 2. Exponential Bound + Binary Search ⭐ Go-to: O(log k) time, O(1) space
Double the right bound until it passes the target, then binary search.
**Why it's the go-to:** it's the textbook answer to "unknown size". Also, `hi = 10⁴` works under these constraints, but the interviewer wants the doubling.

## Dry Run (Approach 2)
`target = 2`.

| phase | lo | hi | probe | value | action |
|-------|----|----|-------|-------|--------|
| bound | 0 | 1 | get(1) | 0 < 2 | lo = 1, hi = 2 |
| bound | 1 | 2 | get(2) | 3 ≥ 2 | stop |
| search | 1 | 2 | mid 1 | 0 < 2 | lo = 2 |
| search | 2 | 2 | mid 2 | 3 > 2 | hi = 1 |
| search | 2 | 1 | | lo > hi | return **−1** |

## Edge Case Check
- Length 1, target is it → get(1) = sentinel ≥ target, search [0, 1] finds index 0. ✅
- Target bigger than everything → doubling stops once hi is past the end; the search ends at −1. ✅
- Target smaller than get(0) → bound loop stops immediately; search ends at −1. ✅

## ⚠️ Pitfalls
- **Starting `hi = 0` and doubling** → 0 · 2 = 0 forever. Start at 1.
- **Not moving `lo = hi`** while doubling: still correct, but the search window becomes [0, hi] instead of [hi/2, hi].
- **Overflow when doubling** in other settings: here hi stays ≤ ~2 · 10⁴, but guard `hi < INT_MAX / 2` in general.

## 🎯 What the Interviewer Wants
- Use the sentinel as +∞ and keep the array "sorted".
- Exponential search and its O(log k) cost (k = target index, not n).
- A correct standard binary search afterwards.

## Follow-ups
- **Known size:** [LC 0704 Binary Search](../0704-binary-search/)
- **First true of a predicate with an expensive API:** [LC 0278 First Bad Version](../0278-first-bad-version/)
- **Insertion point instead of −1:** [LC 0035 Search Insert Position](../0035-search-insert-position/)
