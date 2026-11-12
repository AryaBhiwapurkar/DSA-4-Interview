---
number: 448
title: Find All Numbers Disappeared in an Array
difficulty: Easy
topic: Arrays & Hashing
pattern: Sign marking (index as hash)
link: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
lists: [Interview Extras]
followup_of: []
related: ["0041 First Missing Positive", "0442 Find All Duplicates in an Array", "0268 Missing Number"]
---

# 0448. Find All Numbers Disappeared in an Array

## ⚡ 30-Second Summary
**Pattern:** Mark "value v seen" by making `nums[v − 1]` negative
**Key insight:** All values are in 1..n, so every value names a valid index. For each value v (read as `|nums[i]|`, since it may already be negated), negate `nums[v − 1]` if it's still positive. Indices that stay positive were never named: i + 1 is missing.
**Go-to:** Negation marking, O(n) time, O(1) extra (output excluded)

## Problem
An array of n integers holds values in 1..n, some repeated. Return every number in 1..n that doesn't appear. Follow-up: no extra space beyond the output. [LeetCode](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

**Examples:**
```
Input:  nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
Why:    2 and 3 appear twice, which leaves no room for 5 and 6.

Input:  nums = [1,1]
Output: [2]
Why:    1 twice, so 2 is missing.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; **1 ≤ nums[i] ≤ n** (this guarantee makes the trick possible).
- Follow-up: O(n) time, no extra space (the returned list doesn't count).

## Hints
<details><summary>Hint 1</summary>
Every value is a valid index (after subtracting 1). How could you record "seen" without a separate array?
</details>
<details><summary>Hint 2</summary>
Values are all positive. What spare information can a number carry without losing its value?
</details>
<details><summary>Hint 3</summary>
For each x: j = |x| − 1; if nums[j] &gt; 0, set nums[j] = −nums[j]. Afterwards, every i with nums[i] &gt; 0 means i + 1 is missing.
</details>

## Clarifying Questions
- Are all values guaranteed in 1..n? (Yes.)
- Can the input be modified? (Yes; restore the signs afterwards if the caller needs it.)
- Does the output order matter? (Ascending is natural; any order is accepted.)

## Example Walkthrough
`[2,2]` (n = 2). Value 2 → negate index 1 → [2,−2]. Value |−2| = 2 → index 1 is already negative, skip. Index 0 is still positive → 1 is missing. Answer [1].

## Approaches

### 1. Hash Set (or Boolean Array): O(n) time, O(n) space
Record what's present, then list the absent values. Simple, but uses extra space.

### 2. Negation Marking ⭐ Go-to: O(n) time, O(1) extra
**Why it's the go-to:** it meets the follow-up, and the same index-as-hash idea solves 0041 and 0442.

(Cyclic placement, as in 0041, also works: put each v at v − 1, then report the slots that don't match.)

## Dry Run (Approach 2)
`[4,3,2,7,8,2,3,1]`

| x read | index | array after |
|--------|-------|-------------|
| 4 | 3 | [4,3,2,−7,8,2,3,1] |
| 3 | 2 | [4,3,−2,−7,8,2,3,1] |
| −2 → 2 | 1 | [4,−3,−2,−7,8,2,3,1] |
| −7 → 7 | 6 | [4,−3,−2,−7,8,2,−3,1] |
| 8 | 7 | [4,−3,−2,−7,8,2,−3,−1] |
| 2 | 1 | already negative |
| −3 → 3 | 2 | already negative |
| −1 → 1 | 0 | [−4,−3,−2,−7,8,2,−3,−1] |

Still positive: indices 4 and 5 → **[5,6]**.

## Edge Case Check
- Nothing missing `[1,2,3]` → []. ✅
- All the same `[1,1,1]` → [2,3]. ✅
- n = 1 → [] (the only value must be 1). ✅

## ⚠️ Pitfalls
- **Reading `nums[i]` without `abs`** after it has been negated gives a negative index.
- **Negating twice** flips a mark back to positive. Only negate when it's still positive (or always use `-abs(...)`).
- **Mutating the caller's array** may be unexpected; mention it, or restore the signs at the end.

## 🎯 What the Interviewer Wants
- Spot that values double as indices.
- The sign-marking trick, with `abs` handled correctly.
- O(1) extra space, with output space excluded explicitly.

## Follow-ups
- **Smallest missing positive, arbitrary values:** [LC 0041 First Missing Positive](../0041-first-missing-positive/)
- **Values seen twice instead of never:** LC 0442 Find All Duplicates in an Array (not added yet). Report j + 1 when nums[j] is already negative.
- **Exactly one missing in 0..n:** [LC 0268 Missing Number](../../18-bit-manipulation/0268-missing-number/)
