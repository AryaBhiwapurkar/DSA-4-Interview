---
number: 167
title: Two Sum II - Input Array Is Sorted
difficulty: Medium
topic: Two Pointers
pattern: Converging pointers on sorted
link: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0001 Two Sum"]
related: ["0001 Two Sum", "0015 3Sum", "0653 Two Sum IV - Input is a BST"]
---

# 0167. Two Sum II - Input Array Is Sorted

## ⚡ 30-Second Summary
**Pattern:** Converging two pointers on a sorted array
**Key insight:** With l at the smallest and r at the largest: if the sum is too small, only moving l right can help; if too big, only moving r left can help. Each step safely discards one element.
**Go-to:** Two pointers, O(n) time, O(1) space

## Problem
Given a 1-indexed array sorted in non-decreasing order and a target, return the 1-based indices `[i, j]` (i < j) of the two numbers that add up to the target. Exactly one solution exists; use only constant extra space. [LeetCode](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)

**Examples:**
```
Input:  numbers = [2,7,11,15], target = 9
Output: [1,2]
Why:    2 + 7 = 9, at 1-based positions 1 and 2.

Input:  numbers = [2,3,4], target = 6
Output: [1,3]
Why:    2 + 4 = 6.

Input:  numbers = [-1,0], target = -1
Output: [1,2]
Why:    -1 + 0 = -1.
```

**Constraints:**
- 2 ≤ n ≤ 3·10⁴; -1000 ≤ numbers[i], target ≤ 1000.
- Sorted non-decreasing; exactly one answer; O(1) extra space required.

## Hints
<details><summary>Hint 1</summary>
The hashmap from Two Sum works but uses O(n) space. What does sortedness give you?
</details>
<details><summary>Hint 2</summary>
Start with the smallest and largest elements. If their sum is too small, which pointer should move?
</details>
<details><summary>Hint 3</summary>
Too small: l++. Too big: r--. Equal: return [l+1, r+1].
</details>

## Clarifying Questions
- 1-based or 0-based output? (1-based.)
- Exactly one answer? (Yes.)
- Can the same element be used twice? (No.)
- Extra space allowed? (Only O(1).)

## Example Walkthrough
`numbers = [2,3,4], target = 6`
- l = 0 (2), r = 2 (4): 6 = target. Return [1, 3].

## Approaches

### 1. Binary Search per Element: O(n log n) time, O(1) space
For each i, binary search `target - numbers[i]` in `(i, n)`. Uses sortedness but not optimally.

### 2. Hashmap (Two Sum): O(n) time, O(n) space
Works, but violates the O(1)-space requirement.

### 3. Two Pointers ⭐ Go-to: O(n) time, O(1) space
Move l up or r down depending on the sum.
**Why it's the go-to:** optimal time and the required constant space, in five lines.

## Dry Run (Approach 3)
`numbers = [2,7,11,15], target = 9`

| l | r | numbers[l] | numbers[r] | sum | action |
|---|---|------------|------------|-----|--------|
| 0 | 3 | 2 | 15 | 17 | too big, r-- |
| 0 | 2 | 2 | 11 | 13 | too big, r-- |
| 0 | 1 | 2 | 7 | 9 | found, return [1,2] |

## Edge Case Check
- Negatives, `[-1,0]`: sum -1 found immediately. ✅
- Duplicates, `[1,1,3]`, target 2: l = 0, r = 2 (4 too big), r = 1: 2. ✅
- n = 2: one check. ✅

## ⚠️ Pitfalls
- **Returning 0-based indices:** the answer is 1-based.
- **Why it's correct:** when the sum is too small, numbers[l] can't pair with anything ≤ numbers[r], so dropping it is safe. Be ready to explain this.
- **Overflow in general variants:** values here are tiny; with large values use 64-bit sums.

## 🎯 What the Interviewer Wants
- Use the sorted property; meet the O(1) space requirement.
- A clear argument for why moving a pointer never skips the answer.

## Follow-ups
- **Unsorted input:** hashmap: [LC 0001 Two Sum](../../01-arrays-hashing/0001-two-sum/)
- **Three numbers summing to zero:** sort + fix one + this: [LC 0015 3Sum](../0015-3sum/)
- **Input is a BST:** in-order iterators from both ends: LC 0653 Two Sum IV - Input is a BST (not added yet)
- **Count pairs with sum < target:** when the sum is small, all pairs (l, l+1..r) count: add r - l, then l++.
