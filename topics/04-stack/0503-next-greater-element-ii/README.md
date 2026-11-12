---
number: 503
title: Next Greater Element II
difficulty: Medium
topic: Stack
pattern: Monotonic stack over two passes (circular)
link: https://leetcode.com/problems/next-greater-element-ii/
lists: [Interview Extras]
followup_of: ["0496 Next Greater Element I"]
related: ["0496 Next Greater Element I", "0739 Daily Temperatures", "0901 Online Stock Span"]
---

# 0503. Next Greater Element II

## ⚡ 30-Second Summary
**Pattern:** Simulate the wrap-around by scanning 2n indices with `i % n`
**Key insight:** In a circular array, an element's next greater may lie before it, after wrapping. Walk the array twice, keeping a stack of **indices** whose answer is still unknown. Each element's answer is the first bigger value met in either pass. Push only in the first pass. The second pass just resolves leftovers. Anything still on the stack after that is a maximum and gets −1.
**Go-to:** Monotonic stack of indices over 2n steps, O(n) time, O(n) space

## Problem
Given a circular array, where the element after the last is the first, return for each element the first strictly larger value found by moving forward (wrapping around), or −1. [LeetCode](https://leetcode.com/problems/next-greater-element-ii/)

**Examples:**
```
Input:  nums = [1,2,1]
Output: [2,-1,2]
Why:    The last 1 wraps around to find 2; 2 is the maximum.

Input:  nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]
Why:    The final 3 wraps to the start and meets 4 after 1, 2, 3.
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; values may repeat (−10⁹..10⁹).

## Hints
<details><summary>Hint 1</summary>
How would you handle "circular" without actually copying the array?
</details>
<details><summary>Hint 2</summary>
Values repeat, so you can't key a map by value. What should the stack hold?
</details>
<details><summary>Hint 3</summary>
ans = [−1]·n. For i in 0..2n−1: x = nums[i % n]; while stack and nums[stack.top] &lt; x: ans[pop()] = x. If i &lt; n, push i.
</details>

## Clarifying Questions
- Strictly greater? (Yes; equal values don't count.)
- Duplicates? (Yes, so store indices.)
- Wrap at most once? (Yes, one full circle.)

## Example Walkthrough
`[1,2,1]`: first pass gives ans[0] = 2, and indices 1 and 2 are left on the stack (values 2, 1). Second pass: i = 3 (value 1) resolves nothing. i = 4 (value 2) pops index 2, so ans[2] = 2. Index 1 stays → −1.

## Approaches

### 1. Scan Forward per Element: O(n²) time, O(1) space
For each i, check j = i+1 .. i+n−1 modulo n.

### 2. Two-pass Monotonic Stack ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** the 0496 template plus one modulo trick; each index is pushed once and popped at most once.

## Dry Run (Approach 2)
`[1,2,3,4,3]`

| i | i % n | x | pops → ans | stack (indices) |
|---|-------|---|------------|-----------------|
| 0 | 0 | 1 | – | [0] |
| 1 | 1 | 2 | ans[0]=2 | [1] |
| 2 | 2 | 3 | ans[1]=3 | [2] |
| 3 | 3 | 4 | ans[2]=4 | [3] |
| 4 | 4 | 3 | – | [3,4] |
| 5 | 0 | 1 | – | |
| 6 | 1 | 2 | – | |
| 7 | 2 | 3 | – | |
| 8 | 3 | 4 | ans[4]=4 | [3] |
| 9 | 4 | 3 | – | **[2,3,4,−1,4]** |

## Edge Case Check
- All equal → all −1 (strict comparison). ✅
- n = 1 → [−1]. ✅
- The maximum → −1 even after wrapping. ✅

## ⚠️ Pitfalls
- **Pushing in the second pass too:** harmless but wasteful, and can confuse the index bookkeeping. Push only when i < n.
- **Map keyed by value** (as in 0496) breaks with duplicates.
- **Copying the array** to length 2n works but uses extra memory. `% n` avoids it.

## 🎯 What the Interviewer Wants
- The circular trick (2n with modulo).
- Indices on the stack, plus strict comparison.
- O(n).

## Follow-ups
- **Non-circular, subset queries:** [LC 0496 Next Greater Element I](../0496-next-greater-element-i/)
- **Distances:** [LC 0739 Daily Temperatures](../0739-daily-temperatures/)
- **Next greater number with the same digits:** LC 0556 Next Greater Element III (not added yet). That's Next Permutation on digits.
