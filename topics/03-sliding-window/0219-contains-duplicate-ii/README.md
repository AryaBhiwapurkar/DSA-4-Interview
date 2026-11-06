---
number: 219
title: Contains Duplicate II
difficulty: Easy
topic: Sliding Window
pattern: Fixed window + set
link: https://leetcode.com/problems/contains-duplicate-ii/
lists: [LC Top Interview 150]
followup_of: ["0217 Contains Duplicate"]
related: ["0217 Contains Duplicate", "0220 Contains Duplicate III"]
---

# 0219. Contains Duplicate II

## ⚡ 30-Second Summary
**Pattern:** Fixed-size sliding window backed by a hash set
**Key insight:** "Two equal values at most k apart" means: when you reach index i, is nums[i] among the previous k values? Keep exactly those k values in a set; add the new one and evict the one that falls out of range.
**Go-to:** Window set of size k, O(n) time, O(min(n, k)) space

## Problem
Given an integer array and k, return true if there are two different indices i and j with `nums[i] == nums[j]` and `|i - j| ≤ k`. [LeetCode](https://leetcode.com/problems/contains-duplicate-ii/)

**Examples:**
```
Input:  nums = [1,2,3,1], k = 3
Output: true
Why:    The two 1s are at indices 0 and 3, distance 3 ≤ 3.

Input:  nums = [1,0,1,1], k = 1
Output: true
Why:    The 1s at indices 2 and 3 are adjacent.

Input:  nums = [1,2,3,1,2,3], k = 2
Output: false
Why:    Every repeat is exactly 3 apart, which is more than 2.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; -10⁹ ≤ nums[i] ≤ 10⁹ (use hashing, not a counting array).
- 0 ≤ k ≤ 10⁵ (k can exceed n; k = 0 is always false).

## Hints
<details><summary>Hint 1</summary>
For index i, which earlier indices could possibly pair with it?
</details>
<details><summary>Hint 2</summary>
You need fast "is this value in the last k elements?" checks.
</details>
<details><summary>Hint 3</summary>
Maintain a set of the last k values. Before inserting nums[i], check membership; after inserting, remove nums[i-k] if the window is too big.
</details>

## Clarifying Questions
- Is the distance condition ≤ k or < k? (≤ k.)
- Can k be 0 or larger than n? (Yes to both.)
- Return a boolean only? (Yes.)

## Example Walkthrough
`nums = [1,2,3,1,2,3], k = 2`
- Window holds at most 2 values. i = 3 (1): window {2,3}, no 1. i = 4 (2): window {3,1}, no 2. i = 5 (3): window {1,2}, no 3.
- False.

## Approaches

### 1. Brute Force: O(n·k) time, O(1) space
For each i, check the next k elements. Up to 10¹⁰ at the limits.

### 2. Last-Seen Hashmap: O(n) time, O(n) space
Map value → last index. At i, if `i - last[nums[i]] ≤ k`, return true; then update last. Equally fast; stores every distinct value.

### 3. Window Set ⭐ Go-to: O(n) time, O(min(n, k)) space
Check `nums[i]` in the set; insert it; if the set size exceeds k, remove `nums[i-k]`.
**Why it's the go-to:** it's the fixed-window template, uses only O(k) memory, and is the natural lead-in to the III variant.

## Dry Run (Approach 3)
`nums = [1,0,1,1], k = 1`

| i | nums[i] | window (before) | in window? | window (after) |
|---|---------|-----------------|------------|----------------|
| 0 | 1 | {} | no | {1} |
| 1 | 0 | {1} | no | {1,0} → evict nums[0] → {0} |
| 2 | 1 | {0} | no | {0,1} → evict nums[1] → {1} |
| 3 | 1 | {1} | yes | return true |

## Edge Case Check
- k = 0: the window is always empty after eviction; never true. ✅
- k ≥ n: reduces to Contains Duplicate. ✅
- Duplicate exactly k apart: still inside the window when checked. ✅

## ⚠️ Pitfalls
- **Evicting before checking** (or evicting nums[i-k-1]) makes the window off by one.
- **Evicting a value that appears twice in the window:** can't happen; if it were in the window twice you'd have returned true already.
- **C++/Go map default values:** with the last-seen map, a missing key looks like index 0; use find / comma-ok.

## 🎯 What the Interviewer Wants
- Translate "≤ k apart" into a fixed-size window.
- Correct insert/evict order.
- Compare with the last-index map and the space trade-off.

## Follow-ups
- **No distance limit:** [LC 0217 Contains Duplicate](../../01-arrays-hashing/0217-contains-duplicate/)
- **Values within t, indices within k:** buckets of width t+1 or an ordered set in the window: LC 0220 Contains Duplicate III (not added yet)
