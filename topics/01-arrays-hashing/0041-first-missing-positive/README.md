---
number: 41
title: First Missing Positive
difficulty: Hard
topic: Arrays & Hashing
pattern: Cyclic placement (index as hash)
link: https://leetcode.com/problems/first-missing-positive/
lists: [Interview Extras]
followup_of: []
related: ["0448 Find All Numbers Disappeared in an Array", "0268 Missing Number", "0287 Find the Duplicate Number", "0442 Find All Duplicates in an Array"]
---

# 0041. First Missing Positive

## ⚡ 30-Second Summary
**Pattern:** Use the array itself as a hash table: value v belongs at index v − 1
**Key insight:** The answer is always in 1..n+1, because n numbers can fill 1..n at most. Ignore everything outside 1..n. Swap each value v into slot v − 1 until every slot holds its own value or junk. Then the first index i with `nums[i] ≠ i + 1` gives the answer i + 1. If every slot is correct, the answer is n + 1.
**Go-to:** Cyclic swaps, O(n) time, O(1) extra space

## Problem
Given an unsorted integer array, return the smallest positive integer that isn't in it. You must use O(n) time and O(1) extra space. [LeetCode](https://leetcode.com/problems/first-missing-positive/)

**Examples:**
```
Input:  nums = [1,2,0]
Output: 3
Why:    1 and 2 are present; 3 is the first gap.

Input:  nums = [3,4,-1,1]
Output: 2
Why:    1 is there but 2 isn't.

Input:  nums = [7,8,9,11,12]
Output: 1
Why:    Nothing in 1..n is present, so 1 is missing.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; values span the full 32-bit range (negatives, zeros, duplicates, huge numbers).
- O(n) time **and** O(1) extra space: no sorting, no hash set.

## Hints
<details><summary>Hint 1</summary>
With n numbers, what's the largest the answer could possibly be?
</details>
<details><summary>Hint 2</summary>
Only values 1..n matter. Could each of them be stored at a position determined by its value?
</details>
<details><summary>Hint 3</summary>
For each i: while 1 ≤ nums[i] ≤ n and nums[nums[i] − 1] ≠ nums[i], swap nums[i] with nums[nums[i] − 1]. Then return the first i + 1 with nums[i] ≠ i + 1, else n + 1.
</details>

## Clarifying Questions
- Can the input be modified? (Yes; that's how O(1) space is reached.)
- Duplicates, negatives, zeros? (All possible.)
- Is the answer guaranteed ≤ n + 1? (Yes, by pigeonhole.)

## Example Walkthrough
`[3,4,-1,1]` (n = 4). At i = 0: 3 goes to slot 2 → [-1,4,3,1]; −1 is junk, so stop. At i = 1: 4 goes to slot 3 → [-1,1,3,4]; 1 goes to slot 0 → [1,-1,3,4]; −1 is junk. Slots 2 and 3 are already correct. Scan: index 1 holds −1 ≠ 2 → answer 2.

## Approaches

### 1. Sort and Scan: O(n log n) time, O(1) extra
Sort, then walk positives looking for the first gap (skip duplicates). Breaks the time limit in the statement.

### 2. Hash Set: O(n) time, O(n) space
Put everything in a set, then test 1, 2, 3, … Simple, but breaks the space limit.

### 3. Cyclic Placement ⭐ Go-to: O(n) time, O(1) extra
**Why it's the go-to:** it meets both limits. Each swap puts one value in its final slot, so there are at most n swaps in total, despite the nested loop.

(The alternative O(1) trick marks presence by negating `nums[v − 1]`, after first replacing non-positives with n + 1. Same complexity, a bit more fiddly.)

## Dry Run (Approach 3)
`[3,4,-1,1]`

| i | action | array |
|---|--------|-------|
| 0 | 3 → slot 2 (swap with −1) | [-1,4,3,1] |
| 0 | −1 out of range, next i | |
| 1 | 4 → slot 3 (swap with 1) | [-1,1,3,4] |
| 1 | 1 → slot 0 (swap with −1) | [1,-1,3,4] |
| 1 | −1 out of range | |
| 2, 3 | already home | |
| scan | i = 1: −1 ≠ 2 | **2** |

## Edge Case Check
- `[1]` → 2 (all slots correct → n + 1). ✅
- Duplicates `[1,1]` → the `nums[v−1] ≠ v` check stops the infinite swap → 2. ✅
- All out of range `[7,8,9]` → 1. ✅

## ⚠️ Pitfalls
- **Swap loop condition `nums[i] ≠ i + 1`** instead of `nums[nums[i]−1] ≠ nums[i]` loops forever on duplicates.
- **Python simultaneous assignment** `nums[i], nums[nums[i]-1] = ...` evaluates the left targets in order, and `nums[i]` changes first. Save `v = nums[i]` and swap `nums[i], nums[v-1]`.
- **Treating 0 or negatives as valid** values to place.
- **Claiming O(n²)** because of the nested loop: every swap fixes one slot, so the total is O(n).

## 🎯 What the Interviewer Wants
- The 1..n+1 bound, stated up front.
- An in-place placement or marking scheme, and an amortised O(n) argument.
- Duplicate and junk handling without infinite loops.

## Follow-ups
- **List every missing number in 1..n:** [LC 0448 Find All Numbers Disappeared in an Array](../0448-find-all-numbers-disappeared-in-an-array/)
- **Exactly one missing in 0..n:** [LC 0268 Missing Number](../../18-bit-manipulation/0268-missing-number/)
- **Find duplicates in place:** LC 0442 Find All Duplicates in an Array (not added yet). Same sign-marking idea.
- **Read-only array:** [LC 0287 Find the Duplicate Number](../../06-linked-list/0287-find-the-duplicate-number/) uses Floyd instead.
