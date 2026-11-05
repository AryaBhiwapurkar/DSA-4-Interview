---
number: 135
title: Candy
difficulty: Hard
topic: Greedy
pattern: Two passes L→R, R→L
link: https://leetcode.com/problems/candy/
lists: [LC Top Interview 150]
followup_of: []
related: ["0042 Trapping Rain Water", "0238 Product of Array Except Self"]
---

# 0135. Candy

## ⚡ 30-Second Summary
**Pattern:** Two greedy passes, one per neighbour constraint
**Key insight:** Split the rule in two. The left pass gives each child 1 + their left neighbour's candies when rated higher. The right pass does the same from the right, taking `max` so the left constraint survives. Each pass assigns the minimum its own constraint needs, so the combined answer is the minimum overall.
**Go-to:** Two passes, O(n) time, O(n) space

## Problem
Children stand in a line with ratings. Every child gets at least one candy, and any child with a higher rating than an adjacent child must get more candies than that neighbour. Return the minimum total. [LeetCode](https://leetcode.com/problems/candy/)

**Examples:**
```
Input:  ratings = [1,0,2]
Output: 5
Why:    [2,1,2]: the middle child is lowest, both ends beat it.

Input:  ratings = [1,2,2]
Output: 4
Why:    [1,2,1]: equal ratings impose nothing, so the last child can drop back to 1.
```

**Constraints:**
- 1 ≤ n ≤ 2·10⁴, so O(n²) relaxation is borderline; O(n) is expected.
- Equal neighbours have **no** constraint between them.

## Hints
<details><summary>Hint 1</summary>
Each child has two constraints, one per neighbour. Can you satisfy just the left-neighbour constraint for everyone in one sweep?
</details>
<details><summary>Hint 2</summary>
Now sweep from the right for the right-neighbour constraint. How do you avoid breaking what the first sweep set up?
</details>
<details><summary>Hint 3</summary>
c = all 1s. Left to right: if r[i] > r[i-1], c[i] = c[i-1] + 1. Right to left: if r[i] > r[i+1], c[i] = max(c[i], c[i+1] + 1). Return sum(c).
</details>

## Clarifying Questions
- Do equal ratings need equal candies? (No, no constraint at all.)
- Is it a line or a circle? (Line.)
- Return the total only? (Yes.)

## Example Walkthrough
`[1,2,87,87,87,2,1]`: the left pass gives [1,2,3,1,1,1,1] (equal 87s reset to 1). The right pass fixes the descent: [1,2,3,1,3,2,1]. Total 13. The middle 87 stays at 1 because its neighbours are equal, not lower.

## Approaches

### 1. Repeated Relaxation: O(n²) time, O(n) space
Start with all 1s and keep fixing violations until a full sweep changes nothing. Correct, but a long descent needs many sweeps.

### 2. Two Passes ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** the decomposition into two independent constraints is easy to explain and hard to get wrong.

### 3. One Pass over Slopes: O(n) time, O(1) space
Count the lengths of up and down runs; a down run that gets longer than the preceding up run forces the peak to grow by one. Impressive, but fiddly under pressure. Mention it as the O(1)-space follow-up.

## Dry Run (Approach 2)
`[1,2,5,4,3,2]`

| i | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| ratings | 1 | 2 | 5 | 4 | 3 | 2 |
| after left pass | 1 | 2 | 3 | 1 | 1 | 1 |
| after right pass | 1 | 2 | **4** | 3 | 2 | 1 |

The peak 5 needs 3 from the left but 4 from the right (it sits above a descent of length 3); max picks 4. Total **13**.

## Edge Case Check
- One child → 1. ✅
- Strictly decreasing `[3,2,1]` → [3,2,1] = 6. ✅
- Plateaus `[1,2,2]` → equal neighbours reset to 1 → 4. ✅

## ⚠️ Pitfalls
- **Overwriting instead of taking max** in the right pass breaks the left constraint at peaks.
- **Treating equal ratings as "must be equal"** overcounts.
- **One pass with both neighbours** fails: the right neighbour's value isn't known yet.
- **Slope version:** the peak adjustment (`peak >= down`) is easy to get off by one; test descents longer and shorter than the ascent.

## 🎯 What the Interviewer Wants
- Split the two-sided constraint into two one-sided passes.
- Argue minimality: each pass assigns the least its own constraint allows.
- Optionally, the O(1)-space slope method.

## Follow-ups
- **Same left/right two-pass idea:** [LC 0042 Trapping Rain Water](../../02-two-pointers/0042-trapping-rain-water/), [LC 0238 Product of Array Except Self](../../01-arrays-hashing/0238-product-of-array-except-self/)
- **Return the actual distribution:** return `c` instead of its sum.
