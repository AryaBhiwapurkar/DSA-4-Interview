---
number: 1899
title: Merge Triplets to Form Target Triplet
difficulty: Medium
topic: Greedy
pattern: Filter valid triplets
link: https://leetcode.com/problems/merge-triplets-to-form-target-triplet/
lists: [NeetCode 150]
followup_of: []
related: ["0055 Jump Game", "0763 Partition Labels"]
---

# 1899. Merge Triplets to Form Target Triplet

## ⚡ 30-Second Summary
**Pattern:** Greedy filter
**Key insight:** A merge takes the max of each coordinate, so values can only grow. Any triplet with a coordinate **above** target would poison the result: discard it. Every other triplet is harmless to merge, so merge them all, and the target is reachable iff each coordinate is matched exactly by some usable triplet.
**Go-to:** One pass with three "found" flags, O(n) time, O(1) space

## Problem
You may repeatedly replace one triplet with the element-wise max of it and another. Decide whether some triplet can end up exactly equal to target. [LeetCode](https://leetcode.com/problems/merge-triplets-to-form-target-triplet/)

**Examples:**
```
Input:  triplets = [[2,5,3],[1,8,4],[1,7,5]], target = [2,7,5]
Output: true
Why:    Skip [1,8,4] (its 8 overshoots). Merging [2,5,3] and [1,7,5] gives [2,7,5].

Input:  triplets = [[3,4,5],[4,5,6]], target = [3,2,5]
Output: false
Why:    Every triplet has a middle value above 2, and merges never shrink a value.

Input:  triplets = [[2,5,3],[2,3,4],[1,2,5],[5,2,3]], target = [5,5,5]
Output: true
Why:    All are usable; merging [2,5,3], [1,2,5] and [5,2,3] gives [5,5,5].
```

**Constraints:**
- 1 ≤ n ≤ 10⁵, values in [1, 1000].
- Only one pass is needed.

## Hints
<details><summary>Hint 1</summary>
Can a merge ever decrease a coordinate? What does that say about triplets with any value larger than the target's?
</details>
<details><summary>Hint 2</summary>
Among the remaining triplets, does merging an extra one ever hurt?
</details>
<details><summary>Hint 3</summary>
Skip triplets where any t[i] > target[i]. For the rest, mark found[i] when t[i] == target[i]. Answer: all three found.
</details>

## Clarifying Questions
- Is the target itself in the list sometimes? (Possibly; that's covered.)
- Values positive? (Yes, 1..1000.)
- Any limit on the number of merges? (No.)

## Example Walkthrough
`[[2,1,1],[1,2,1]], target [2,2,2]`: both are usable. Coordinates 0 and 1 are matched, but no triplet has a 2 in coordinate 2. Merging both gives [2,2,1] ≠ target → false.

## Approaches

### 1. Merge Every Usable Triplet: O(n) time, O(1) space
Element-wise max over all non-overshooting triplets, then compare with target. Very direct.

### 2. Found Flags ⭐ Go-to: O(n) time, O(1) space
Same filter; record which coordinates are hit exactly.
**Why it's the go-to:** it states the proof (each coordinate needs an exact hit from a safe triplet) right in the code. Both are fine.

## Dry Run (Approach 2)
`[[2,5,3],[1,8,4],[1,7,5]]`, target `[2,7,5]`

| triplet | overshoots? | exact hits | found |
|---------|-------------|------------|-------|
| [2,5,3] | no | coord 0 (2) | [T, F, F] |
| [1,8,4] | yes (8 > 7) | skip | [T, F, F] |
| [1,7,5] | no | coords 1, 2 | [T, T, T] |

All found → **true**.

## Edge Case Check
- One triplet equal to target → true. ✅
- Every triplet overshoots somewhere (example 2) → false. ✅
- All coordinates covered except one (`[[2,1,1],[1,2,1]]`, `[2,2,2]`) → false. ✅

## ⚠️ Pitfalls
- **Marking found from an overshooting triplet:** [1,8,4] must be ignored entirely, even if one coordinate matches.
- **Trying to search merge orders:** order doesn't matter; max is commutative and associative.
- **Comparing with ≥ instead of ==** for found: a smaller value never reaches the target.

## 🎯 What the Interviewer Wants
- The monotonicity argument (max never decreases), so filter first.
- The "merging safe triplets never hurts" step.
- A one-pass O(n) solution.

## Follow-ups
- **Greedy with a reachability invariant:** [LC 0055 Jump Game](../0055-jump-game/)
- **k-dimensional target:** same filter, k flags.
- **Minimum number of triplets to merge:** for each coordinate pick any safe exact match, so at most 3.
