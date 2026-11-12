---
number: 719
title: Find K-th Smallest Pair Distance
difficulty: Hard
topic: Binary Search
pattern: Binary search on the answer + two-pointer count
link: https://leetcode.com/problems/find-k-th-smallest-pair-distance/
lists: [Interview Extras]
followup_of: []
related: ["0378 Kth Smallest Element in a Sorted Matrix", "0668 Kth Smallest Number in Multiplication Table", "0410 Split Array Largest Sum"]
---

# 0719. Find K-th Smallest Pair Distance

## ⚡ 30-Second Summary
**Pattern:** "k-th smallest of an implicit set" → binary search on the value, then count
**Key insight:** You can't list all n² distances, but you can count how many are ≤ d in O(n). Sort the array and slide a window: for each right end r, move l until `nums[r] − nums[l] ≤ d`; the window adds r − l pairs. The count grows with d, so the answer is the smallest d with count(d) ≥ k.
**Go-to:** Sort + binary search on distance + sliding-window count, O(n log n + n log W) time, O(1) extra space

## Problem
The distance of a pair is the absolute difference of its two values. Over all pairs i < j, return the k-th smallest distance. [LeetCode](https://leetcode.com/problems/find-k-th-smallest-pair-distance/)

**Examples:**
```
Input:  nums = [1,3,1], k = 1
Output: 0
Why:    Distances are 2, 0, 2; the smallest is 0 (the two 1s).

Input:  nums = [1,1,1], k = 2
Output: 0
Why:    All three pairs have distance 0.

Input:  nums = [1,6,1], k = 3
Output: 5
Why:    Distances sorted are 0, 5, 5; the third is 5.
```

**Constraints:**
- 2 ≤ n ≤ 10⁴ (so ~5 · 10⁷ pairs); 0 ≤ nums[i] ≤ 10⁶; 1 ≤ k ≤ n(n−1)/2.

## Hints
<details><summary>Hint 1</summary>
Listing every pair is up to 5 · 10⁷ items. Instead, can you count how many distances are ≤ some d?
</details>
<details><summary>Hint 2</summary>
After sorting, for each right index r the valid partners form a contiguous block ending at r − 1, and its left edge only moves right as r grows.
</details>
<details><summary>Hint 3</summary>
Binary search d over [0, max − min]: count(d) ≥ k → hi = d, otherwise lo = d + 1. count is a two-pointer sweep adding r − l for each r.
</details>

## Clarifying Questions
- Pairs are unordered with i < j, so each pair counts once? (Yes.)
- Duplicates allowed, so distance 0 is possible? (Yes.)
- Is k 1-indexed? (Yes.)

## Example Walkthrough
`[1,6,1], k = 3` → sorted [1,1,6]. count(4): pairs (1,1) only → 1 < 3. count(5): (1,1), (1,6), (1,6) → 3 ≥ 3. Smallest such d is 5.

## Approaches

### 1. All Pairs + Sort: O(n² log n) time, O(n²) space
Generate every distance, sort, and take index k − 1. About 5 · 10⁷ items: too much memory and time.

### 2. Binary Search on Distance + Two-pointer Count ⭐ Go-to: O(n log n + n log W) time, O(1) extra space
W = max − min ≤ 10⁶, so about 20 counting passes.
**Why it's the go-to:** the standard way to get "the k-th smallest of something you can't list"; the count is a simple sliding window.

(A bucket count over distances 0..W is O(n² + W): fine for small n, but still quadratic.)

## Dry Run (Approach 2)
`nums = [1,3,5,9]` (distances 2,2,4,4,6,8), k = 4. lo = 0, hi = 8.

| lo | hi | mid | count(mid) | ≥ 4? | action |
|----|----|-----|------------|------|--------|
| 0 | 8 | 4 | (1,3) (1,5) (3,5) (5,9) = 4 | yes | hi = 4 |
| 0 | 4 | 2 | (1,3) (3,5) = 2 | no | lo = 3 |
| 3 | 4 | 3 | 2 | no | lo = 4 |
| 4 | 4 | | | | return **4** |

## Edge Case Check
- All equal → every distance 0 → count(0) = all pairs → 0. ✅
- k = total pairs → answer max − min. ✅
- n = 2 → a single pair. ✅

## ⚠️ Pitfalls
- **Forgetting to sort** before the two-pointer count.
- **"Is mid an actual distance?"** It is: count only changes at real distances, so the smallest d with count ≥ k is one of them.
- **Resetting l for each r** makes the count O(n²); l only moves forward.
- **Count overflow:** up to 5 · 10⁷ pairs fits in int, but use 64-bit if n can be larger.

## 🎯 What the Interviewer Wants
- Spot "k-th smallest over an implicit set" → binary search on value + count.
- An O(n) monotone two-pointer count.
- The argument that the answer is a real distance.

## Follow-ups
- **Same idea on a sorted matrix:** LC 0378 Kth Smallest Element in a Sorted Matrix (not added yet)
- **Same idea on a multiplication table:** LC 0668 Kth Smallest Number in Multiplication Table (not added yet)
- **Binary search on the answer with a greedy check:** [LC 0410 Split Array Largest Sum](../0410-split-array-largest-sum/)
