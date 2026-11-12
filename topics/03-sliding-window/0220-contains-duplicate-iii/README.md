---
number: 220
title: Contains Duplicate III
difficulty: Hard
topic: Sliding Window
pattern: Index window + value buckets (or ordered set)
link: https://leetcode.com/problems/contains-duplicate-iii/
lists: [Interview Extras]
followup_of: ["0219 Contains Duplicate II"]
related: ["0219 Contains Duplicate II", "0217 Contains Duplicate", "0164 Maximum Gap"]
---

# 0220. Contains Duplicate III

## ⚡ 30-Second Summary
**Pattern:** Sliding window over indices, buckets over values
**Key insight:** Keep only the last indexDiff elements in the window. Split the values into buckets of width `w = valueDiff + 1`. Two values in the same bucket differ by at most valueDiff, so that's an immediate hit. Otherwise only the two neighbouring buckets can hold a close value, so check them. Each bucket holds at most one value, since a second one would already have been a hit. That makes every step O(1).
**Go-to:** Bucketing, O(n) time, O(min(n, indexDiff)) space

## Problem
Decide whether two different indices i and j exist with `|i − j| ≤ indexDiff` and `|nums[i] − nums[j]| ≤ valueDiff`. [LeetCode](https://leetcode.com/problems/contains-duplicate-iii/)

**Examples:**
```
Input:  nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
Output: true
Why:    The two 1s are 3 apart with value difference 0.

Input:  nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
Output: false
Why:    Within any 3 consecutive positions, values differ by at least 4.
```

**Constraints:**
- 2 ≤ n ≤ 10⁵; values span the 32-bit range, so differences need 64-bit.
- 1 ≤ indexDiff ≤ n; 0 ≤ valueDiff ≤ 10⁹.

## Hints
<details><summary>Hint 1</summary>
The index condition is a fixed-size window. Within the window, what query do you need to answer?
</details>
<details><summary>Hint 2</summary>
"Is there a value within valueDiff of x?" A sorted structure answers it with lower_bound. Can you do it in O(1) with buckets?
</details>
<details><summary>Hint 3</summary>
w = valueDiff + 1, id = floor(x / w). Same id → true. Neighbour id ± 1 with |difference| ≤ valueDiff → true. Insert x, and remove nums[i − indexDiff]'s bucket once the window is full.
</details>

## Clarifying Questions
- Indices must differ? (Yes, i ≠ j.)
- Negative values? (Yes, so use floor division for bucket ids.)
- Overflow? (Differences can reach 2³²; use 64-bit.)

## Example Walkthrough
`[1,5,9,1], indexDiff = 3, valueDiff = 3` → w = 4. 1 → bucket 0. 5 → bucket 1; neighbour bucket 0 holds 1, |5−1| = 4 > 3. 9 → bucket 2; neighbour 1 holds 5, diff 4. The next 1 → bucket 0, which still holds 1 (index 0 is within 3) → true.

## Approaches

### 1. Check Each Pair in Range: O(n · indexDiff) time, O(1) space
For each i, compare with the next indexDiff elements. Too slow when both are large.

### 2. Ordered Set Window: O(n log k) time, O(k) space
Keep the window's values in a balanced BST. For x, find the smallest value ≥ x − valueDiff and check it's ≤ x + valueDiff. Clean in C++ (`std::set::lower_bound`); Python needs a third-party sorted container.

### 3. Buckets ⭐ Go-to: O(n) time, O(k) space
**Why it's the go-to:** linear, uses only a hashmap, and the pigeonhole argument behind it is short.

## Dry Run (Approach 3)
`[1,5,9,1,5,9], indexDiff = 2, valueDiff = 3` → w = 4

| i | x | bucket | same? | neighbours | remove | buckets after |
|---|---|--------|-------|------------|--------|---------------|
| 0 | 1 | 0 | no | – | – | {0:1} |
| 1 | 5 | 1 | no | b0=1: diff 4 | – | {0:1, 1:5} |
| 2 | 9 | 2 | no | b1=5: diff 4 | drop nums[0] (b0) | {1:5, 2:9} |
| 3 | 1 | 0 | no | b1=5: diff 4 | drop nums[1] (b1) | {2:9, 0:1} |
| 4 | 5 | 1 | no | b0=1, b2=9: diff 4 | drop nums[2] (b2) | {0:1, 1:5} |
| 5 | 9 | 2 | no | b1=5: diff 4 | | → **false** |

## Edge Case Check
- valueDiff = 0 → w = 1, so this becomes plain duplicate detection in the window. ✅
- Negative values → floor division puts −1 in bucket −1, not 0. ✅
- Extreme values → 64-bit differences avoid overflow. ✅

## ⚠️ Pitfalls
- **Truncating division in C++** puts −3 and 3 both in bucket 0 when w = 4. Use floor: `x >= 0 ? x / w : (x + 1) / w − 1`.
- **Removing too early or late:** after processing index i, drop nums[i − indexDiff] so the window holds the last indexDiff values.
- **int overflow** in `abs(a − b)` or `valueDiff + 1`. Use long long.
- **Bucket width valueDiff** instead of valueDiff + 1 breaks the "same bucket means a hit" guarantee for valueDiff = 0.

## 🎯 What the Interviewer Wants
- Combine an index window with a value-proximity query.
- The ordered-set solution, then buckets for O(n).
- Careful handling of negatives and overflow.

## Follow-ups
- **Exact duplicates within distance k:** [LC 0219 Contains Duplicate II](../0219-contains-duplicate-ii/)
- **Buckets for max gap in O(n):** LC 0164 Maximum Gap (not added yet)
