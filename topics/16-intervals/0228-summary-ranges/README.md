---
number: 228
title: Summary Ranges
difficulty: Easy
topic: Intervals
pattern: Linear scan of runs
link: https://leetcode.com/problems/summary-ranges/
lists: [LC Top Interview 150]
followup_of: []
related: ["0163 Missing Ranges", "0352 Data Stream as Disjoint Intervals", "0128 Longest Consecutive Sequence"]
---

# 0228. Summary Ranges

## ⚡ 30-Second Summary
**Pattern:** Linear scan over runs of consecutive values
**Key insight:** The array is sorted with no duplicates, so a run continues exactly while `nums[i+1] == nums[i] + 1`. Remember where the run started, extend it, then output "start->end" (or just "start" for a run of length 1).
**Go-to:** One scan with a run start, O(n) time, O(1) extra space

## Problem
A sorted array of distinct integers is given. Cover it with the smallest list of ranges of consecutive numbers, writing each range as "a->b", or as "a" when it holds one number. [LeetCode](https://leetcode.com/problems/summary-ranges/)

**Examples:**
```
Input:  nums = [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Why:    The breaks are between 2 and 4, and between 5 and 7.

Input:  nums = [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Why:    0 and 6 are isolated, so they print alone.
```

**Constraints:**
- 0 ≤ n ≤ 20. **Empty input is allowed.**
- Values span the full int range, so `nums[i] + 1` can overflow in C++.

## Hints
<details><summary>Hint 1</summary>
When does a run of consecutive numbers end?
</details>
<details><summary>Hint 2</summary>
Remember the first value of the current run and keep stepping while the next value is exactly one more.
</details>
<details><summary>Hint 3</summary>
For each run: start = nums[i]; while nums[i+1] == nums[i] + 1, i++. Output start alone if start == nums[i], else "start->nums[i]". Move on to i + 1.
</details>

## Clarifying Questions
- Sorted and distinct? (Yes.)
- Empty input? (Return [].)
- Format for single numbers? ("7", not "7->7".)

## Example Walkthrough
`[0,2,3,4,6,8,9]`: run at 0 stops immediately (2 ≠ 1) → "0". Run at 2 goes through 3, 4 and stops at 6 → "2->4". 6 alone → "6". 8, 9 → "8->9".

## Approaches

### 1. Group by value − index: O(n) time, O(n) space
Inside a run, value − index is constant, so group by it (Python's `groupby`). Neat, but less obvious.

### 2. One Scan ⭐ Go-to: O(n) time, O(1) extra
**Why it's the go-to:** the most direct code, and the overflow edge case is easy to show.

## Dry Run (Approach 2)
`[0,1,2,4,5,7]`

| run start | extends through | output |
|-----------|-----------------|--------|
| 0 | 1, 2 (4 ≠ 3 stops) | "0->2" |
| 4 | 5 (7 ≠ 6 stops) | "4->5" |
| 7 | end of array | "7" |

## Edge Case Check
- Empty → []. ✅
- Single element `[-1]` → ["-1"]. ✅
- `[INT_MIN, INT_MAX]` → two singletons, no overflow. ✅

## ⚠️ Pitfalls
- **C++ `nums[i] + 1` at INT_MAX** overflows (undefined behaviour); widen to `long long`.
- **`nums[i+1] - nums[i] == 1`** overflows too for `[INT_MIN, INT_MAX]`.
- **Printing "a->a"** for single numbers.
- **Forgetting the last run** when the loop ends.

## 🎯 What the Interviewer Wants
- A clean one-pass loop with no leftover-run bug.
- The overflow case without being prompted.
- Correct output formatting.

## Follow-ups
- **Ranges missing from [lower, upper]:** LC 0163 Missing Ranges (not added yet). Same scan over the gaps.
- **Numbers arrive one by one:** LC 0352 Data Stream as Disjoint Intervals (not added yet). Sorted map of intervals.
- **Unsorted input, longest run:** [LC 0128 Longest Consecutive Sequence](../../01-arrays-hashing/0128-longest-consecutive-sequence/)
