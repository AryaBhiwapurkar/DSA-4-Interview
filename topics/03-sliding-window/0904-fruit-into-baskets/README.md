---
number: 904
title: Fruit Into Baskets
difficulty: Medium
topic: Sliding Window
pattern: Longest window with at most 2 distinct values
link: https://leetcode.com/problems/fruit-into-baskets/
lists: [Interview Extras]
followup_of: []
related: ["0340 Longest Substring with At Most K Distinct Characters", "0159 Longest Substring with At Most Two Distinct Characters", "1004 Max Consecutive Ones III"]
---

# 0904. Fruit Into Baskets

## ⚡ 30-Second Summary
**Pattern:** "Longest subarray with at most 2 distinct values" in disguise
**Key insight:** Two baskets, each holding one fruit type, and you pick consecutive trees. That's the longest window with ≤ 2 distinct values. Use the at-most-K template with K = 2 and a count map; shrink from the left while there are more than two types.
**Go-to:** Shrinking window + count map, O(n) time, O(1) space (at most 3 keys)

## Problem
Trees stand in a row, each bearing one fruit type. Start at any tree and move right, picking one fruit from each tree, but you only have two baskets and each holds a single type. Stop at the first tree whose type fits neither basket. Return the most fruit you can pick. [LeetCode](https://leetcode.com/problems/fruit-into-baskets/)

**Examples:**
```
Input:  fruits = [1,2,1]
Output: 3
Why:    Only two types in the whole row.

Input:  fruits = [0,1,2,2]
Output: 3
Why:    [1,2,2]; starting at 0 you'd stop at the 2.

Input:  fruits = [1,2,3,2,2]
Output: 4
Why:    [2,3,2,2].
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, so O(n) is expected.

## Hints
<details><summary>Hint 1</summary>
Strip the story away: what kind of subarray are you picking?
</details>
<details><summary>Hint 2</summary>
A contiguous run with at most two distinct values, as long as possible. Which window template fits?
</details>
<details><summary>Hint 3</summary>
cnt[f[r]]++; while len(cnt) &gt; 2: decrement cnt[f[l]], erase at 0, l++. best = max(best, r − l + 1).
</details>

## Clarifying Questions
- Must the picking be contiguous? (Yes, you move right without skipping.)
- Exactly two baskets? (Yes; K = 2.)
- Can the answer be the whole array? (Yes, if it has ≤ 2 types.)

## Example Walkthrough
`[1,2,3,2,2]`. [1,2] is valid (2). Adding 3 makes three types, so drop 1 → [2,3]. Then [2,3,2] and [2,3,2,2] → length 4.

## Approaches

### 1. Every Start: O(n²) time
Extend from each start until a third type appears.

### 2. Shrinking Window + Map ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** it's literally LC 340 with k = 2, and naming that reduction is what the interviewer wants to see.

(A map-free variant tracks the last two types and the length of the current trailing run of the latest type. It's O(1) without a map, but easier to get wrong.)

## Dry Run (Approach 2)
`[0,1,2,2]`

| r | fruit | counts | shrink | l | len | best |
|---|-------|--------|--------|---|-----|------|
| 0 | 0 | {0:1} | | 0 | 1 | 1 |
| 1 | 1 | {0:1,1:1} | | 0 | 2 | 2 |
| 2 | 2 | {0:1,1:1,2:1} | drop 0 | 1 | 2 | 2 |
| 3 | 2 | {1:1,2:2} | | 1 | 3 | **3** |

## Edge Case Check
- One tree → 1. ✅
- All the same type → n. ✅
- Alternating three types `[1,2,3,1,2,3]` → 2. ✅

## ⚠️ Pitfalls
- **Not erasing zero counts:** the distinct-type check breaks.
- **Treating it as "two most frequent types overall":** the picking must be contiguous.

## 🎯 What the Interviewer Wants
- Translate the story into "longest window with ≤ 2 distinct".
- The window template with correct shrinking.

## Follow-ups
- **General k:** [LC 0340 Longest Substring with At Most K Distinct Characters](../0340-longest-substring-with-at-most-k-distinct-characters/)
- **Count windows with exactly k types:** [LC 0992 Subarrays with K Different Integers](../0992-subarrays-with-k-different-integers/)
