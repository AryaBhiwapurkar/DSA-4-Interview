---
number: 312
title: Burst Balloons
difficulty: Hard
topic: 2-D Dynamic Programming
pattern: Interval DP (last to burst)
link: https://leetcode.com/problems/burst-balloons/
lists: [NeetCode 150]
followup_of: []
related: ["1039 Minimum Score Triangulation of Polygon", "1547 Minimum Cost to Cut a Stick", "0664 Strange Printer"]
---

# 0312. Burst Balloons

## ⚡ 30-Second Summary
**Pattern:** Interval DP, choosing the **last** element of the interval
**Key insight:** Choosing the first balloon to burst fails, because the neighbours keep changing. Choose the **last** balloon k to burst inside the open interval (l, r): when it goes, its neighbours are exactly l and r, and the two sides (l, k) and (k, r) are independent. `best(l, r) = max over k of a[l]·a[k]·a[r] + best(l, k) + best(k, r)`, with 1s padded on both ends.
**Go-to:** Interval memo on (l, r), O(n³) time, O(n²) space

## Problem
Balloons in a row carry numbers. Bursting one earns the product of its number and its current left and right neighbours (missing neighbours count as 1), and then the neighbours become adjacent. Burst all of them and return the maximum total. [LeetCode](https://leetcode.com/problems/burst-balloons/)

**Examples:**
```
Input:  nums = [3,1,5,8]
Output: 167
Why:    Burst 1, then 5, then 3, then 8: 3·1·5 + 3·5·8 + 1·3·8 + 1·8·1 = 15 + 120 + 24 + 8.

Input:  nums = [1,5]
Output: 10
Why:    Burst 1 first (1·1·5 = 5), then 5 alone (5). Doing 5 first gives 5 + 1 = 6.
```

**Constraints:**
- 1 ≤ n ≤ 300, 0 ≤ nums[i] ≤ 100. O(n³) = 2.7·10⁷ is fine; n! is not.
- Totals stay below 3·10⁸, so int is enough.

## Hints
<details><summary>Hint 1</summary>
If you pick which balloon to burst first, the two remaining sides still interact through their neighbours. Is there a choice that splits the problem into independent halves?
</details>
<details><summary>Hint 2</summary>
Think about the balloon burst last in a range. At that moment, who are its neighbours?
</details>
<details><summary>Hint 3</summary>
Pad nums with 1 on each side → a. best(l, r) = max over l < k < r of a[l]*a[k]*a[r] + best(l, k) + best(k, r); best(l, r) = 0 when r = l + 1. Answer best(0, n+1).
</details>

## Clarifying Questions
- Missing neighbours count as 1? (Yes.)
- Zeros allowed? (Yes; they make any product they're in 0.)
- Return the maximum total only? (Yes.)

## Example Walkthrough
`[1,5]` padded to `[1,1,5,1]`. Interval (0, 3) with last k = 2 (the 5): 1·5·1 = 5, plus best(0, 2) = 1·1·5 = 5 (the 1 burst earlier, with the 5 still next to it) → 10. With last k = 1 (the 1): 1·1·1 + best(1, 3) = 1 + 1·5·1 = 6. Max 10.

## Approaches

### 1. Brute Force over Orders: O(n!) time, O(n) space
Try every burst order recursively. Only viable for tiny n; useful to check the DP.

### 2. Interval Memo, Last Burst ⭐ Go-to: O(n³) time, O(n²) space
O(n²) intervals × O(n) choices of k.
**Why it's the go-to:** the recursion states the "last balloon" insight directly; you don't need to get the bottom-up loop order right under pressure.

### 3. Bottom-up by Length: O(n³) time, O(n²) space
Fill dp[l][r] for increasing r - l so the sub-intervals are ready. Same complexity, no recursion.

## Dry Run (Approach 2)
`[3,1,5,8]` padded to a = [1,3,1,5,8,1] (indices 0..5).

| interval (l, r) | best | last k (value) |
|-----------------|------|----------------|
| (1,3) | 3·1·5 = 15 | 2 (1) |
| (2,4) | 1·5·8 = 40 | 3 (5) |
| (1,4) | 3·5·8 + 15 + 0 = 135 | 3 (5) |
| (0,4) | 1·3·8 + 0 + 135 = 159 | 1 (3) |
| (0,5) | 1·8·1 + 159 + 0 = **167** | 4 (8) |

Read top-down: 8 goes last, before it 3, before that 5, and the 1 goes first. That's the order in example 1.

## Edge Case Check
- One balloon `[7]` → 1·7·1 = 7. ✅
- Zeros: a 0 balloon contributes 0 whenever it's involved; the DP still picks the best order. ✅
- Two balloons → burst the smaller first. ✅

## ⚠️ Pitfalls
- **Choosing the first balloon to burst**: subproblems aren't independent.
- **Forgetting the padding**: edge balloons need the virtual 1s.
- **Closed vs open intervals:** with open (l, r), the base case is r = l + 1 → 0.
- **Bottom-up loop order:** iterate by interval length, not by l from 0.
- **Python memo recursion** depth is about n, which is fine here.

## 🎯 What the Interviewer Wants
- The "last burst" reframing and why it makes the halves independent.
- O(n³) interval DP, top-down or bottom-up.
- Recognise the same pattern in matrix-chain and polygon triangulation problems.

## Follow-ups
- **Same "split at k" structure:** LC 1039 Minimum Score Triangulation of Polygon (not added yet)
- **Cut costs depend on the current stick:** LC 1547 Minimum Cost to Cut a Stick (not added yet). Sort the cuts, pad the ends, same DP.
- **Interval DP on strings:** LC 0664 Strange Printer (not added yet)
