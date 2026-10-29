---
number: 239
title: Sliding Window Maximum
difficulty: Hard
topic: Sliding Window
pattern: Monotonic deque
link: https://leetcode.com/problems/sliding-window-maximum/
lists: [NeetCode 150]
followup_of: []
related: ["0155 Min Stack", "0862 Shortest Subarray with Sum at Least K", "1438 Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit", "0739 Daily Temperatures"]
---

# 0239. Sliding Window Maximum

## ⚡ 30-Second Summary
**Pattern:** Monotonic decreasing deque of indices
**Key insight:** If a newer element is ≥ an older one, the older one can never be a window max again (the newer one outlives it). So keep a deque of indices with strictly decreasing values: the front is always the current max; pop the front when it leaves the window.
**Go-to:** Monotonic deque, O(n) time, O(k) space

## Problem
Given an array and a window size k, slide the window from left to right one step at a time and return the maximum of each window.

**Examples:**
```
Input:  nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Why:    Windows [1,3,-1]→3, [3,-1,-3]→3, [-1,-3,5]→5, [-3,5,3]→5, [5,3,6]→6, [3,6,7]→7.

Input:  nums = [1], k = 1
Output: [1]
Why:    One window of one element.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; 1 ≤ k ≤ n, so O(n·k) can be 10¹⁰.
- -10⁴ ≤ nums[i] ≤ 10⁴.

## Hints
<details><summary>Hint 1</summary>
A heap gives the max, but how do you remove elements that left the window?
</details>
<details><summary>Hint 2</summary>
If nums[j] ≥ nums[i] and j > i, is nums[i] ever useful again?
</details>
<details><summary>Hint 3</summary>
Keep indices in a deque with decreasing values: pop from the back while the new value is ≥ the back; pop from the front if it's outside the window; the front is the max.
</details>

## Clarifying Questions
- Is k always valid (1 ≤ k ≤ n)? (Yes.)
- Output length? (n - k + 1.)
- Duplicates? (Yes; pop on ≥ or > both work if consistent.)

## Example Walkthrough
`nums = [1,3,-1,-3,5,3,6,7], k = 3`
- Push 1; 3 pops 1; push -1. Window full → max 3.
- -3 pushed (deque values 3,-1,-3) → 3. 5 arrives: 3 left the window and 5 pops -1, -3 → 5.
- 3 pushed → 5. 6 pops 3 and 5 → 6. 7 pops 6 → 7.

## Approaches

### 1. Brute Force: O(n·k) time, O(1) space
Scan each window for its max.

### 2. Max-Heap With Lazy Deletion: O(n log n) time, O(n) space
Push (value, index); before reading the top, pop entries whose index is outside the window.

### 3. Monotonic Deque ⭐ Go-to: O(n) time, O(k) space
Each index is pushed and popped at most once.
**Why it's the go-to:** linear, and it's the canonical monotonic-queue problem; interviewers expect it for a Hard.

## Dry Run (Approach 3)
`nums = [1,3,-1,-3,5,3,6,7], k = 3` (deque shows indices:values)

| i | nums[i] | pop front (out of window) | pop back (≤ new) | deque after | output |
|---|---------|---------------------------|------------------|-------------|--------|
| 0 | 1 | - | - | 0:1 | |
| 1 | 3 | - | 0 | 1:3 | |
| 2 | -1 | - | - | 1:3, 2:-1 | 3 |
| 3 | -3 | - | - | 1:3, 2:-1, 3:-3 | 3 |
| 4 | 5 | 1 | 2, 3 | 4:5 | 5 |
| 5 | 3 | - | - | 4:5, 5:3 | 5 |
| 6 | 6 | - | 5, 4 | 6:6 | 6 |
| 7 | 7 | - | 6 | 7:7 | 7 |

## Edge Case Check
- k = 1: output equals input. ✅
- k = n: single max. ✅
- Strictly decreasing input: deque holds k items; front expires each step. ✅
- All equal: popping on ≤ keeps the deque at size 1. ✅

## ⚠️ Pitfalls
- **Storing values instead of indices:** you can't tell when the front left the window.
- **Expiry check:** front index ≤ i - k means it's out.
- **Emitting output too early:** only from i ≥ k - 1.
- **Python:** use `collections.deque`; `list.pop(0)` is O(n).

## 🎯 What the Interviewer Wants
- Why the dominated elements can be discarded (the monotonic invariant).
- Amortized O(n) argument.
- Heap with lazy deletion as a fallback.

## Follow-ups
- **Window minimum:** flip the comparison (increasing deque).
- **Longest subarray with max - min ≤ limit:** two deques + variable window: LC 1438 (not added yet)
- **Next greater element (no window):** monotonic stack: LC 0739 Daily Temperatures (not added yet)
- **O(1) max/min with push/pop at one end:** LC 0155 Min Stack (not added yet)
