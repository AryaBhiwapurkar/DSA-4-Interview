---
number: 31
title: Next Permutation
difficulty: Medium
topic: Arrays & Hashing
pattern: Pivot, swap with next larger, reverse suffix
link: https://leetcode.com/problems/next-permutation/
lists: [Interview Extras]
followup_of: []
related: ["0046 Permutations", "0047 Permutations II", "0060 Permutation Sequence", "0556 Next Greater Element III"]
---

# 0031. Next Permutation

## ⚡ 30-Second Summary
**Pattern:** Find the pivot, swap it with its successor, reverse the suffix
**Key insight:** The longest non-increasing suffix is already at its maximum, so the change must happen just before it. That position is the pivot i, the rightmost index with `a[i] < a[i+1]`. Swap a[i] with the smallest suffix value that's still bigger than it (the rightmost one > a[i]). The suffix stays non-increasing, so reverse it to make it as small as possible. If there's no pivot, the whole array is the last permutation: reverse everything.
**Go-to:** Three-step scan from the right, O(n) time, O(1) space

## Problem
Rearrange an integer array, in place, into the next lexicographically larger ordering of its elements. If it's already the largest ordering, wrap around to the smallest (ascending). [LeetCode](https://leetcode.com/problems/next-permutation/)

**Examples:**
```
Input:  nums = [1,2,3]
Output: [1,3,2]
Why:    The smallest change is at the last two positions.

Input:  nums = [3,2,1]
Output: [1,2,3]
Why:    Already the largest ordering, so wrap to the smallest.

Input:  nums = [1,1,5]
Output: [1,5,1]
Why:    Duplicates are fine: 1,5,1 is the next distinct ordering.
```

**Constraints:**
- 1 ≤ n ≤ 100; 0 ≤ nums[i] ≤ 100; duplicates allowed.
- In place, O(1) extra memory.

## Hints
<details><summary>Hint 1</summary>
Write the permutations of [1,2,3] in order. Which part of the array changes from one to the next?
</details>
<details><summary>Hint 2</summary>
A suffix that only decreases can't be made larger by rearranging it. So where must the change happen?
</details>
<details><summary>Hint 3</summary>
i = rightmost index with a[i] &lt; a[i+1]. If none, reverse all. Else j = rightmost index with a[j] &gt; a[i]; swap a[i], a[j]; reverse a[i+1:].
</details>

## Clarifying Questions
- In place? (Yes, O(1) extra.)
- Duplicates? (Yes; use strict `<` and `>` so equal values are skipped.)
- What happens after the last permutation? (Wrap to sorted ascending.)

## Example Walkthrough
`[1,3,5,4,2]`. Suffix [5,4,2] is non-increasing, so the pivot is 3 at index 1. The rightmost suffix value > 3 is 4. Swap → [1,4,5,3,2]. Reverse the suffix [5,3,2] → [2,3,5]. Result **[1,4,2,3,5]**.

## Approaches

### 1. Generate All Permutations: O(n!·n) time, O(n!·n) space
Generate, sort, find the current one, return the next. Only worth mentioning to dismiss.

### 2. Pivot + Swap + Reverse ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** three linear scans, in place, and each step has a one-sentence justification.

(C++ has `std::next_permutation`, which does exactly this. Mention it, but write it by hand.)

## Dry Run (Approach 2)
`[1,1,5]`

| step | detail | array |
|------|--------|-------|
| find pivot | i = 1 (1 < 5) | [1,1,5] |
| find successor | j = 2 (5 > 1) | |
| swap | a[1] ↔ a[2] | [1,5,1] |
| reverse suffix | [1] alone | **[1,5,1]** |

## Edge Case Check
- n = 1 → unchanged. ✅
- All equal `[2,2,2]` → no pivot → reverse → unchanged. ✅
- Fully descending → wraps to ascending. ✅

## ⚠️ Pitfalls
- **`<=` instead of `<`** when finding the pivot with duplicates picks the wrong position.
- **Sorting the suffix** works but costs O(n log n). It's already non-increasing, so a reverse is enough.
- **Swapping with the first larger element from the left** of the suffix, instead of the rightmost, breaks with duplicates.
- **C++ `size_t i = n - 2`** underflows when n = 1. Use `int`.

## 🎯 What the Interviewer Wants
- The non-increasing-suffix observation.
- The three steps, each justified, in O(n) and in place.
- Duplicates and the wrap-around case handled.

## Follow-ups
- **All permutations:** [LC 0046 Permutations](../../10-backtracking/0046-permutations/), LC 0047 Permutations II (not added yet)
- **k-th permutation directly:** LC 0060 Permutation Sequence (not added yet). Factorial number system.
- **Next larger number with the same digits:** LC 0556 Next Greater Element III (not added yet). This algorithm on digits, plus an overflow check.
- **Previous permutation:** mirror every comparison.
