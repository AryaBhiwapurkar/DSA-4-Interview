---
number: 402
title: Remove K Digits
difficulty: Medium
topic: Stack
pattern: Greedy monotonic increasing stack
link: https://leetcode.com/problems/remove-k-digits/
lists: [Interview Extras]
followup_of: []
related: ["0316 Remove Duplicate Letters", "0321 Create Maximum Number", "1673 Find the Most Competitive Subsequence"]
---

# 0402. Remove K Digits

## ⚡ 30-Second Summary
**Pattern:** Keep digits in non-decreasing order; drop a bigger digit when a smaller one follows
**Key insight:** For the smallest result, the leftmost digits matter most. Whenever the current digit is smaller than the stack top and removals are left, pop the top: putting the smaller digit earlier always wins. When the scan ends with removals still left, the stack is non-decreasing, so cut from the end. Strip leading zeros and return "0" if nothing remains.
**Go-to:** Monotonic stack, O(n) time, O(n) space

## Problem
Given a number as a digit string and an integer k, remove exactly k digits so the remaining number is as small as possible. Return it as a string without leading zeros ("0" if empty). [LeetCode](https://leetcode.com/problems/remove-k-digits/)

**Examples:**
```
Input:  num = "1432219", k = 3
Output: "1219"
Why:    Drop 4, 3 and the first 2 so the remaining digits stay as small as possible from the left.

Input:  num = "10200", k = 1
Output: "200"
Why:    Removing the 1 leaves "0200"; leading zeros go.

Input:  num = "10", k = 2
Output: "0"
Why:    Everything is removed.
```

**Constraints:**
- 1 ≤ k ≤ n ≤ 10⁵; no leading zeros in num except "0" itself.

## Hints
<details><summary>Hint 1</summary>
Compare two results of the same length: which position decides which one is smaller?
</details>
<details><summary>Hint 2</summary>
If a digit is followed by a smaller one, should the bigger one stay?
</details>
<details><summary>Hint 3</summary>
For each d: while k &gt; 0 and stack and stack.top &gt; d: pop, k−−. Push d. Then pop k more from the end, strip leading zeros, return "0" if empty.
</details>

## Clarifying Questions
- Exactly k removals? (Yes.)
- Keep the relative order of the rest? (Yes, it's a subsequence.)
- Leading zeros in the output? (Strip them; empty → "0".)

## Example Walkthrough
`"1432219", k = 3`. Push 1. 4 > 1, push. 3 < 4 → pop 4 (k=2), push 3. 2 < 3 → pop 3 (k=1), push 2. 2 equals the top, push. 1 < 2 → pop 2 (k=0), push 1. Push 9. Stack "1219".

## Approaches

### 1. Remove One Peak at a Time: O(n · k) time
k times, delete the first digit that's bigger than its successor (or the last digit). Correct but slow when k is large.

### 2. Monotonic Stack ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** the same greedy in one pass; every digit is pushed and popped at most once.

## Dry Run (Approach 2)
`"1432219", k = 3`

| digit | pops | k after | stack |
|-------|------|---------|-------|
| 1 | – | 3 | 1 |
| 4 | – | 3 | 14 |
| 3 | 4 | 2 | 13 |
| 2 | 3 | 1 | 12 |
| 2 | – | 1 | 122 |
| 1 | 2 | 0 | 121 |
| 9 | – | 0 | 1219 |

Result **"1219"**.

## Edge Case Check
- k == n → "0". ✅
- Non-decreasing num `"12345", k = 2` → trim the end → "123". ✅
- Leading zeros after removal → stripped; all zeros → "0". ✅

## ⚠️ Pitfalls
- **Forgetting the leftover k** when the input is non-decreasing.
- **Not stripping leading zeros**, or stripping everything and returning "" instead of "0".
- **Popping on `>=`:** popping equal digits wastes removals ("112", k=1 → "11", not "12").

## 🎯 What the Interviewer Wants
- The greedy argument: the leftmost differing digit decides.
- A monotonic stack in O(n), with all three cleanup steps.

## Follow-ups
- **Each letter exactly once, smallest order:** [LC 0316 Remove Duplicate Letters](../0316-remove-duplicate-letters/)
- **Most competitive subsequence of length k:** LC 1673 Find the Most Competitive Subsequence (not added yet). Same stack, with the constraint on remaining length.
- **Maximum number from two arrays:** LC 0321 Create Maximum Number (not added yet)
