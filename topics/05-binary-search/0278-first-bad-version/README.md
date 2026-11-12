---
number: 278
title: First Bad Version
difficulty: Easy
topic: Binary Search
pattern: Lower-bound binary search on a boolean predicate
link: https://leetcode.com/problems/first-bad-version/
lists: [Interview Extras]
followup_of: ["0704 Binary Search"]
related: ["0035 Search Insert Position", "0034 Find First and Last Position of Element in Sorted Array", "0875 Koko Eating Bananas"]
---

# 0278. First Bad Version

## ⚡ 30-Second Summary
**Pattern:** Find the first `true` in a false...false, true...true sequence
**Key insight:** Once a version is bad, every later one is bad too, so `isBadVersion` is monotonic. Binary search for the first `true`: on a bad mid keep it (`hi = mid`), on a good mid skip past it (`lo = mid + 1`).
**Go-to:** Lower-bound binary search, O(log n) API calls, O(1) space

## Problem
Versions 1..n are released in order. From some version on, every version is bad. Using an API `isBadVersion(v)`, find the first bad version with as few calls as possible. [LeetCode](https://leetcode.com/problems/first-bad-version/)

**Examples:**
```
Input:  n = 5, bad = 4
Output: 4
Why:    3 is good and 4 is bad, so 4 is where the bad run starts.

Input:  n = 1, bad = 1
Output: 1
Why:    The only version is bad.
```

**Constraints:**
- 1 ≤ bad ≤ n ≤ 2³¹ − 1: at least one version is bad, and `lo + hi` can overflow a 32-bit int.

## Hints
<details><summary>Hint 1</summary>
What does the sequence of answers from isBadVersion(1), isBadVersion(2), ... look like?
</details>
<details><summary>Hint 2</summary>
It is all good, then all bad. You want the boundary. If mid is bad, can the answer be after mid?
</details>
<details><summary>Hint 3</summary>
Keep the range [lo, hi] that must contain the answer. Bad mid → hi = mid (mid might be it). Good mid → lo = mid + 1. Stop when lo == hi, and compute mid without adding lo and hi directly.
</details>

## Clarifying Questions
- Is at least one version guaranteed bad? (Yes, version n at least.)
- Is the API call the expensive part? (Yes: minimise calls, not just time.)
- Can n be close to INT_MAX? (Yes: watch the midpoint.)

## Example Walkthrough
n = 5, bad = 4. Range [1, 5]: mid = 3 is good → [4, 5]. mid = 4 is bad → [4, 4]. One candidate left: 4. Two API calls.

## Approaches

### 1. Linear Scan: O(n) time, O(1) space
Call the API on 1, 2, 3, … and return the first bad one. Up to 2³¹ calls.

### 2. Lower-bound Binary Search ⭐ Go-to: O(log n) time, O(1) space
Halve [lo, hi] on each call until one version remains.
**Why it's the go-to:** ~31 calls for any n; this is the cleanest "first true" template there is.

## Dry Run (Approach 2)
n = 10, bad = 7.

| lo | hi | mid | isBad(mid) | action |
|----|----|-----|------------|--------|
| 1 | 10 | 5 | no | lo = 6 |
| 6 | 10 | 8 | yes | hi = 8 |
| 6 | 8 | 7 | yes | hi = 7 |
| 6 | 7 | 6 | no | lo = 7 |
| 7 | 7 | | | return **7** |

## Edge Case Check
- n = 1 → loop never runs, returns 1. ✅
- First version bad → hi keeps shrinking to 1. ✅
- Only the last version bad → lo climbs to n. ✅
- n = 2126753390 → `lo + (hi - lo) / 2` stays in range. ✅

## ⚠️ Pitfalls
- **`(lo + hi) / 2` overflows** in C++/Java when both are near 2³¹. Use `lo + (hi - lo) / 2`. (Python ints don't overflow.)
- **`hi = mid - 1` on a bad mid** throws away the answer when mid is the first bad.
- **`while (lo <= hi)` with `hi = mid`** loops forever when lo == hi and mid is bad.

## 🎯 What the Interviewer Wants
- Recognise the monotonic predicate and the "first true" search.
- Correct boundary updates with a loop that always terminates.
- The overflow-safe midpoint without being prompted.

## Follow-ups
- **Plain search in a sorted array:** [LC 0704 Binary Search](../0704-binary-search/)
- **First and last position of a value:** [LC 0034 Find First and Last Position of Element in Sorted Array](../0034-find-first-and-last-position-of-element-in-sorted-array/)
- **Predicate over an answer range instead of indices:** [LC 0875 Koko Eating Bananas](../0875-koko-eating-bananas/)
