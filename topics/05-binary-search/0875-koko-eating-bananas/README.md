---
number: 875
title: Koko Eating Bananas
difficulty: Medium
topic: Binary Search
pattern: Binary search on answer
link: https://leetcode.com/problems/koko-eating-bananas/
lists: [NeetCode 150]
followup_of: []
related: ["1011 Capacity To Ship Packages Within D Days", "0410 Split Array Largest Sum", "1283 Find the Smallest Divisor Given a Threshold", "0069 Sqrt(x)"]
---

# 0875. Koko Eating Bananas

## ⚡ 30-Second Summary
**Pattern:** Binary search on the answer
**Key insight:** If Koko can finish at speed k, she can finish at any speed > k. The predicate "hours(k) ≤ h" is false...false, true...true over k, so binary search finds the first true in [1, max(piles)].
**Go-to:** Binary search on speed k, O(n log max) time, O(1) space

## Problem
There are n piles of bananas and h hours. Each hour Koko picks one pile and eats up to k bananas from it (if the pile has fewer, she finishes it and waits out the hour). Return the minimum integer k that lets her eat everything within h hours. [LeetCode](https://leetcode.com/problems/koko-eating-bananas/)

**Examples:**
```
Input:  piles = [3,6,7,11], h = 8
Output: 4
Why:    At k = 4 the hours are 1+2+2+3 = 8. At k = 3 they're 1+2+3+4 = 10 > 8.

Input:  piles = [30,11,23,4,20], h = 5
Output: 30
Why:    h equals the number of piles, so each pile must go in one hour: k = max pile.

Input:  piles = [30,11,23,4,20], h = 6
Output: 23
Why:    One extra hour lets the 30 pile take two hours at k = 23 (2+1+1+1+1 = 6).
```

**Constraints:**
- 1 ≤ n ≤ 10⁴; n ≤ h ≤ 10⁹ (so an answer always exists).
- 1 ≤ piles[i] ≤ 10⁹: total hours at small k can exceed 32-bit; max(piles) bounds the search.

## Hints
<details><summary>Hint 1</summary>
For a fixed speed k, how many hours does one pile p take?
</details>
<details><summary>Hint 2</summary>
ceil(p / k) per pile. As k grows, total hours never increase. What does that monotonicity let you do?
</details>
<details><summary>Hint 3</summary>
Binary search k over [1, max(piles)]: if hours(k) ≤ h, record k and try smaller (hi = mid), else lo = mid + 1.
</details>

## Clarifying Questions
- Is h ≥ number of piles? (Yes, so k = max(piles) always works.)
- Can she eat from two piles in one hour? (No.)
- Integer speeds only? (Yes.)

## Example Walkthrough
`piles = [3,6,7,11], h = 8`, search k in [1, 11].
- k = 6: hours 1+1+2+2 = 6 ≤ 8, so try smaller: hi = 6.
- k = 3: hours 1+2+3+4 = 10 > 8, too slow: lo = 4.
- k = 5: hours 1+2+2+3 = 8 ≤ 8: hi = 5.
- k = 4: hours 8 ≤ 8: hi = 4. lo == hi = 4.

## Approaches

### 1. Try Every Speed: O(n · max) time, O(1) space
k = 1, 2, 3, … until hours(k) ≤ h. With max up to 10⁹, too slow.

### 2. Binary Search on Speed ⭐ Go-to: O(n log max) time, O(1) space
Lower-bound search for the first k with hours(k) ≤ h.
**Why it's the go-to:** this is THE "binary search on the answer" template; ~30 iterations × n.

## Dry Run (Approach 2)
`piles = [30,11,23,4,20], h = 6`, k in [1, 30]

| lo | hi | mid | hours(mid) | ≤ 6? | action |
|----|----|-----|------------|------|--------|
| 1 | 30 | 15 | 2+1+2+1+2 = 8 | no | lo = 16 |
| 16 | 30 | 23 | 2+1+1+1+1 = 6 | yes | hi = 23 |
| 16 | 23 | 19 | 2+1+2+1+2 = 8 | no | lo = 20 |
| 20 | 23 | 21 | 2+1+2+1+1 = 7 | no | lo = 22 |
| 22 | 23 | 22 | 2+1+2+1+1 = 7 | no | lo = 23 |
| 23 | 23 | | | | return **23** |

## Edge Case Check
- h == n: answer is max(piles). ✅
- h huge (≥ total bananas): answer 1 (lo starts at 1, never 0). ✅
- Single pile `[1000000000]`, h = 2: 500000000. (Covered by the same search; total hours fit in 64-bit.)

## ⚠️ Pitfalls
- **lo = 0**: division by zero in ceil(p / k).
- **Ceil via floats**: `ceil(p / k)` with doubles is fine here but `(p + k - 1) / k` is exact and fast.
- **Overflow of total hours**: at k = 1 the sum can reach 10¹³. Use `long long` in C++ (Go int is 64-bit).
- **Early exit when hours > h** is a valid speedup, but don't break before the sum is computed correctly for the ≤ check.

## 🎯 What the Interviewer Wants
- Spot the monotonic predicate and the search space [1, max(piles)].
- Clean ceil division and overflow awareness.
- Generalize: "minimize the max / minimum capacity / smallest divisor" all use this template.

## Follow-ups
- **Ship packages in D days:** search capacity in [max, sum]: LC 1011 Capacity To Ship Packages Within D Days (not added yet)
- **Split array into k parts minimizing the largest sum:** LC 0410 Split Array Largest Sum (not added yet)
- **Smallest divisor under a threshold:** identical structure: LC 1283 Find the Smallest Divisor Given a Threshold (not added yet)
- **Simpler binary search on the answer:** [LC 0069 Sqrt(x)](../0069-sqrtx/)
