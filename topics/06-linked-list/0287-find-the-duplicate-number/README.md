---
number: 287
title: Find the Duplicate Number
difficulty: Medium
topic: Linked List
pattern: Floyd cycle on indices
link: https://leetcode.com/problems/find-the-duplicate-number/
lists: [NeetCode 150]
followup_of: []
related: ["0141 Linked List Cycle", "0142 Linked List Cycle II", "0041 First Missing Positive", "0448 Find All Numbers Disappeared in an Array"]
---

# 0287. Find the Duplicate Number

## ⚡ 30-Second Summary
**Pattern:** Floyd's cycle detection on the implicit list i → nums[i]
**Key insight:** With n + 1 values in [1, n], treat each value as a "next pointer". Index 0 is never a target, so it's the list's head, and the duplicated value is a node with two incoming edges: exactly the entry of a cycle. Floyd finds that entry in O(1) space.
**Go-to:** Floyd's tortoise and hare (two phases), O(n) time, O(1) space

## Problem
An array of n + 1 integers contains values in [1, n]. Exactly one value repeats (possibly many times). Return it without modifying the array and using O(1) extra space. [LeetCode](https://leetcode.com/problems/find-the-duplicate-number/)

**Examples:**
```
Input:  nums = [1,3,4,2,2]
Output: 2
Why:    2 appears twice.

Input:  nums = [3,1,3,4,2]
Output: 3
Why:    3 appears twice.

Input:  nums = [3,3,3,3,3]
Output: 3
Why:    One value can repeat more than twice.
```

**Constraints:**
- 1 ≤ n ≤ 10⁵; array length n + 1; values in [1, n].
- Don't modify the array; O(1) extra space; less than O(n²) time.

## Hints
<details><summary>Hint 1</summary>
Sorting or a hash set work, but break the constraints. What structure do "values in [1, n] in an array of size n + 1" let you build for free?
</details>
<details><summary>Hint 2</summary>
Follow i → nums[i] starting at 0. Since every value is a valid index, this path never ends, so it must loop. Where does the loop begin?
</details>
<details><summary>Hint 3</summary>
Phase 1: slow = nums[slow], fast = nums[nums[fast]] until they meet. Phase 2: reset one pointer to 0, move both one step at a time; they meet at the duplicate.
</details>

## Clarifying Questions
- Exactly one repeated value? (Yes, but it may appear more than twice.)
- Can I modify the array or use O(n) space? (No to both, per the follow-up.)
- Values always in [1, n]? (Yes, which is what makes the index trick valid.)

## Example Walkthrough
`[1,3,4,2,2]`: links 0 → 1 → 3 → 2 → 4 → 2 → 4 … (cycle 2 ↔ 4).
- Phase 1: slow 1, 3, 2, 4; fast 3, 4, 4, 4. They meet at 4.
- Phase 2: from 0 and 4: (1, 2), (3, 4), (2, 2). They meet at 2, the duplicate.

## Approaches

### 1. Hash Set: O(n) time, O(n) space
Return the first value seen twice. Breaks the O(1) space rule. (Sorting a copy is O(n log n) and also O(n) space.)

### 2. Binary Search on the Value: O(n log n) time, O(1) space
For mid in [1, n], count values ≤ mid. If count > mid, the duplicate is ≤ mid (pigeonhole). Easier to derive than Floyd.

### 3. Floyd Cycle Detection ⭐ Go-to: O(n) time, O(1) space
Two phases: meet inside the cycle, then walk from the start and the meeting point to the entry.
**Why it's the go-to:** the only approach meeting every constraint at O(n); short to code once the mapping is explained. Approach 2 is the safe fallback.

## Dry Run (Approach 3)
`[3,1,3,4,2]`: links 0 → 3 → 4 → 2 → 3 … (cycle 3 → 4 → 2 → 3)

| phase | slow | fast | note |
|-------|------|------|------|
| 1 | 3 | 4 | slow = nums[0]; fast = nums[nums[0]] |
| 1 | 4 | 3 | fast: 4 → 2 → 3 |
| 1 | 2 | 2 | fast: 3 → 4 → 2; meet at 2 |
| 2 | 0 → 3 | 2 → 3 | both 1 step: meet at **3** |

## Edge Case Check
- Value repeated many times `[3,3,3,3,3]`: 0 → 3 → 3, a self-loop at 3; both phases end at 3. ✅
- n = 1 `[1,1]`: 0 → 1 → 1, answer 1. ✅
- Duplicate at the start of the array: fine; the cycle entry is still the duplicate. ✅

## ⚠️ Pitfalls
- **Starting the walk at index n or at nums[0] in phase 2**: the head is index 0, so phase 2 resets to 0.
- **Comparing indices vs values**: in this mapping a "node" is an index and its "next" is nums[index]; the entry node's index equals the duplicate value.
- **Modifying the array** (negative marking or cyclic sort): O(1) space but violates "don't modify".
- **Binary search counting `< mid` instead of `≤ mid`**: shifts the answer by one.

## 🎯 What the Interviewer Wants
- The reduction from array to linked list with a cycle, explained clearly.
- Why the cycle entry is the duplicate (two incoming edges).
- The binary-search-on-value alternative and the trade-offs of each.

## Follow-ups
- **Cycle entry in a real linked list:** same phase 2: LC 0142 Linked List Cycle II (not added yet)
- **Plain cycle detection:** [LC 0141 Linked List Cycle](../0141-linked-list-cycle/)
- **If modification is allowed:** cyclic sort / sign marking: LC 0448 Find All Numbers Disappeared in an Array (not added yet)
- **First missing positive with the same index tricks:** LC 0041 First Missing Positive (not added yet)
