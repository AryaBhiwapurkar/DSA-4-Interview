---
number: 189
title: Rotate Array
difficulty: Medium
topic: Arrays & Hashing
pattern: Reverse in place
link: https://leetcode.com/problems/rotate-array/
lists: [LC Top Interview 150]
followup_of: []
related: ["0061 Rotate List", "0151 Reverse Words in a String", "0048 Rotate Image"]
---

# 0189. Rotate Array

## ⚡ 30-Second Summary
**Pattern:** Triple reversal
**Key insight:** Rotating right by k moves the last k elements to the front. Reverse the whole array, then reverse the first k and the remaining n-k separately: each block ends up in its new place in the right order.
**Go-to:** Three reversals, O(n) time, O(1) space

## Problem
Rotate an integer array to the right by k steps, in place (each step moves the last element to the front). [LeetCode](https://leetcode.com/problems/rotate-array/)

**Examples:**
```
Input:  nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Why:    The last three elements 5,6,7 move to the front.

Input:  nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Why:    The last two elements 3,99 move to the front.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; 0 ≤ k ≤ 10⁵, so k can exceed n (use k mod n).
- Values span the full 32-bit int range.
- Follow-up: do it in place with O(1) extra space.

## Hints
<details><summary>Hint 1</summary>
Rotating by n gives the same array. What does that say about large k?
</details>
<details><summary>Hint 2</summary>
With an extra array, where does nums[i] go?
</details>
<details><summary>Hint 3</summary>
Reverse everything. The block that should be in front is now in front, just backwards. Fix each block with one more reverse.
</details>

## Clarifying Questions
- Right or left rotation? (Right.)
- Can k be larger than n, or 0? (Yes; reduce with k % n.)
- In place required? (Yes, return nothing.)

## Example Walkthrough
`nums = [1,2,3,4,5,6,7], k = 3`
- Reverse all: [7,6,5,4,3,2,1].
- Reverse first 3: [5,6,7,4,3,2,1].
- Reverse last 4: [5,6,7,1,2,3,4].

## Approaches

### 1. Rotate by One, k Times: O(n·k) time, O(1) space
Move the last element to the front, k times. Up to 10¹⁰ steps: too slow.

### 2. Extra Array: O(n) time, O(n) space
`out[(i + k) % n] = nums[i]`, then copy back. Easiest correct answer.

### 3. Three Reversals ⭐ Go-to: O(n) time, O(1) space
`k %= n; reverse(0, n-1); reverse(0, k-1); reverse(k, n-1)`.
**Why it's the go-to:** meets the in-place follow-up with a tiny, memorable trick. (Cyclic replacements is another O(1) method but much easier to get wrong.)

## Dry Run (Approach 3)
`nums = [-1,-100,3,99], k = 2`

| step | array |
|------|-------|
| start | [-1,-100,3,99] |
| reverse all | [99,3,-100,-1] |
| reverse [0..1] | [3,99,-100,-1] |
| reverse [2..3] | [3,99,-1,-100] |

## Edge Case Check
- k = 0 or k = n: k % n = 0, reversals cancel out. ✅
- k > n, `[1,2]`, k = 3: k % 2 = 1, gives [2,1]. ✅
- n = 1: nothing changes. ✅

## ⚠️ Pitfalls
- **Forgetting k %= n:** reversing a prefix of length k > n reads out of bounds.
- **Left vs right:** for a left rotation, reverse the first k and last n-k first, then everything.
- **Python:** `nums = nums[-k:] + nums[:-k]` rebinds the local name and does NOT modify the caller's list; use `nums[:] = ...`. Also `nums[-0:]` is the whole list, so handle k % n == 0.

## 🎯 What the Interviewer Wants
- Reduce k mod n immediately.
- Offer the extra-array solution, then the O(1)-space reversal.
- Explain why the reversal works, not just recite it.

## Follow-ups
- **Rotate a linked list:** [LC 0061 Rotate List](../../06-linked-list/0061-rotate-list/)
- **Reverse word order in place:** same reverse-all-then-each trick: [LC 0151 Reverse Words in a String](../0151-reverse-words-in-a-string/)
- **Rotate a matrix 90°:** [LC 0048 Rotate Image](../../17-math-geometry/0048-rotate-image/)
