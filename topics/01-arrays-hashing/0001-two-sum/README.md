---
number: 1
title: Two Sum
difficulty: Easy
topic: Arrays & Hashing
pattern: Hashmap (complement lookup)
link: https://leetcode.com/problems/two-sum/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0167 Two Sum II - Input Array Is Sorted", "0015 3Sum", "0018 4Sum", "0653 Two Sum IV - Input is a BST"]
---

# 0001. Two Sum

## ⚡ 30-Second Summary
**Pattern:** Hashmap complement lookup
**Key insight:** For each number `x`, the partner I need is `target - x`. Store what I've seen so the lookup is O(1).
**Go-to:** One-pass hashmap, O(n) time, O(n) space

## Problem
Given an integer array and a target, return the indices of the two numbers that add up to the target. Exactly one valid answer exists, and the same element can't be used twice. [LeetCode](https://leetcode.com/problems/two-sum/)

**Examples:**
```
Input:  nums = [2,7,11,15], target = 9
Output: [0,1]
Why:    2 + 7 = 9, and they sit at indices 0 and 1.

Input:  nums = [3,2,4], target = 6
Output: [1,2]
Why:    2 + 4 = 6. Index 0 (3) can't pair with itself to make 6.

Input:  nums = [3,3], target = 6
Output: [0,1]
Why:    Equal values are fine as long as they are different elements.
```

**Constraints:**
- 2 ≤ n ≤ 10⁴, so O(n²) passes but O(n) is expected.
- -10⁹ ≤ nums[i], target ≤ 10⁹, so `target - x` fits in a 32-bit int.
- Exactly one valid answer exists.

## Hints
<details><summary>Hint 1</summary>
Brute force checks every pair. Which part of that work is repeated?
</details>
<details><summary>Hint 2</summary>
If you're at number x, you already know exactly which number you need. What data structure answers "have I seen this value?" fastest?
</details>
<details><summary>Hint 3</summary>
Check for the complement before inserting the current number. Why does the order matter?
</details>

## Clarifying Questions
- Is there always exactly one answer? If none, what should I return?
- Can I use the same element twice? (No.)
- Return indices or values? Does the order of the two indices matter?
- Is the array sorted? (If yes, a better-space approach exists.)
- Can there be negatives or duplicates? (Yes to both, e.g. `[3,3]`, target 6.)
- Size and value range? (n up to 10⁴, values and target in ±10⁹, which matters for overflow.)

## Example Walkthrough
`nums = [3,2,4], target = 6`
- At 3: need 3. Seen nothing yet, so no match. Remember 3.
- At 2: need 4. Not seen. Remember 2.
- At 4: need 2. Seen at index 1, so the answer is [1,2].

Note that at the first step, "need 3" would have matched itself if I had inserted 3 before checking.

## Approaches

### 1. Brute Force: O(n²) time, O(1) space
Try every pair (i, j) with j > i. Simple and correct, but slow for large n.

### 2. Sort + Two Pointers: O(n log n) time, O(n) space
Sort (value, original index) pairs, then move pointers inward based on whether the sum is too small or too big. You need extra space to keep the original indices, so it doesn't beat the hashmap here. It is the go-to when the input is already sorted (see Two Sum II).

### 3. One-Pass Hashmap ⭐ Go-to: O(n) time, O(n) space
For each element, check whether `target - x` is in the map. If it is, return both indices. Otherwise store `x → index`.
**Why it's the go-to:** it's optimal in time, the code is short, and it's easy to explain.

## Dry Run (Approach 3)
`nums = [3,2,4], target = 6`

| i | nums[i] | need | seen (before) | found? | action |
|---|---------|------|---------------|--------|--------|
| 0 | 3 | 3 | {} | no | seen[3]=0 |
| 1 | 2 | 4 | {3:0} | no | seen[2]=1 |
| 2 | 4 | 2 | {3:0, 2:1} | yes, idx 1 | return [1,2] |

## Edge Case Check
- `[3,3]`, target 6: the first 3 isn't in the map yet, then the second 3 finds it, giving [0,1]. ✅
- Negatives, `[-3,4,3,90]`, target 0: need 3 at i=2, found -3 at 0, giving [0,2]. ✅
- Minimum size, n = 2: works in a single check.

## ⚠️ Pitfalls
- **Inserting before checking** lets an element match itself (e.g. `[3]`, target 6).
- **C++ `map[key]` inserts a default value** if the key is missing. Use `find` or `count` for lookups.
- **Overflow:** here `target - x` stays within ±2·10⁹ < INT_MAX (≈2.147·10⁹), so it's safe. It does overflow in **4Sum**, where you need `long long`.
- **Sorting loses original indices** unless you store (value, index) pairs.

## 🎯 What the Interviewer Wants
- State the brute force first, then improve it. Don't jump straight to the hashmap.
- Explain the "complement" idea clearly.
- Name the trade-off: O(n) extra space buys O(n) time.
- Handle duplicates and the check-before-insert order without being prompted.

## Follow-ups
- **Input is sorted?** Use two pointers for O(1) space: [LC 0167 Two Sum II](../../02-two-pointers/0167-two-sum-ii-input-array-is-sorted/)
- **Find all unique triplets summing to 0:** [LC 0015 3Sum](../../02-two-pointers/0015-3sum/)
- **Four numbers, with overflow concerns:** LC 0018 4Sum (not added yet)
- **Input is a BST:** LC 0653 Two Sum IV (not added yet)
- **Numbers arrive as a stream (add/find design):** LC 0170 Two Sum III. Trade-off between a fast `add` and a fast `find`.
- **Return all pairs or count pairs:** a hashmap of counts, with duplicate handling.
- **Closest sum instead of exact:** sort + two pointers, tracking the best difference.
