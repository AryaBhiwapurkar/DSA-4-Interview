---
number: 160
title: Intersection of Two Linked Lists
difficulty: Easy
topic: Linked List
pattern: Two pointers that switch heads (equalise path lengths)
link: https://leetcode.com/problems/intersection-of-two-linked-lists/
lists: [Interview Extras]
followup_of: []
related: ["0141 Linked List Cycle", "0142 Linked List Cycle II", "1650 Lowest Common Ancestor of a Binary Tree III"]
---

# 0160. Intersection of Two Linked Lists

## ⚡ 30-Second Summary
**Pattern:** Walk A then B, and B then A
**Key insight:** Let A have a private part of length a, B a private part of length b, and the shared tail length c. Pointer pa walks A then jumps to B's head; pb walks B then A's head. After a + c + b steps both are at the start of the shared tail. With no intersection, both reach null together after a + b steps.
**Go-to:** Head-switching two pointers, O(m + n) time, O(1) space

## Problem
Given the heads of two singly linked lists, return the node where they start sharing nodes, or null if they never do. The lists have no cycles and must be left unchanged. [LeetCode](https://leetcode.com/problems/intersection-of-two-linked-lists/)

**Examples:**
```
Input:  listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], shared from A[2] / B[3]
Output: the node with value 8
Why:    Both lists continue through the same 8 → 4 → 5 nodes. The 1s have equal values but are different nodes.

Input:  listA = [1,9,1,2,4], listB = [3,2,4], shared from A[3] / B[1]
Output: the node with value 2
Why:    Both end in the same 2 → 4 nodes.

Input:  listA = [2,6,4], listB = [1,5], no shared nodes
Output: null
Why:    The lists never meet.
```

**Constraints:**
- 1 ≤ m, n ≤ 3 · 10⁴; no cycles anywhere.
- Follow-up: O(m + n) time and O(1) memory.

## Hints
<details><summary>Hint 1</summary>
If both lists had the same length before the shared part, you could walk them together and stop at the first common node. Why doesn't that work directly?
</details>
<details><summary>Hint 2</summary>
The private parts differ in length. You could measure both lengths and skip ahead in the longer list. Can you get the same alignment without counting?
</details>
<details><summary>Hint 3</summary>
When a pointer reaches the end of its list, send it to the other list's head. Both then walk a + b + c before the shared part, so they meet there (or both hit null).
</details>

## Clarifying Questions
- Is "intersection" about the same node, not the same value? (Same node.)
- Can either list contain a cycle? (No.)
- Must the lists stay unchanged? (Yes.)

## Example Walkthrough
Example 1: a = 2 (4, 1), b = 3 (5, 6, 1), c = 3 (8, 4, 5). pa walks 4, 1, 8, 4, 5, null, then 5, 6, 1 and reaches the shared 8 on step 9. pb walks 5, 6, 1, 8, 4, 5, null, then 4, 1 and reaches the same 8 on step 9.

## Approaches

### 1. Hash Set of A's Nodes: O(m + n) time, O(m) space
Store every node of A, then return the first node of B that's in the set.

### 2. Length Difference: O(m + n) time, O(1) space
Count both lengths, advance the longer list's pointer by the difference, then walk both together until they're the same node.

### 3. Head-switching Two Pointers ⭐ Go-to: O(m + n) time, O(1) space
Same alignment as approach 2, with no counting.
**Why it's the go-to:** about five lines, and the a + c + b = b + c + a argument is a nice one to explain.

## Dry Run (Approach 3)
Example 1. A's private nodes a0 = 4, a1 = 1; B's private nodes b0 = 5, b1 = 6, b2 = 1; shared c0 = 8, c1 = 4, c2 = 5.

| step | pa | pb |
|------|----|----|
| 0 | a0 | b0 |
| 2 | c0 | b2 |
| 5 | null → next step jumps to B | c2 |
| 6 | b0 | null → next step jumps to A |
| 7 | b1 | a0 |
| 8 | b2 | a1 |
| 9 | **c0** | **c0** → equal, return 8 |

## Edge Case Check
- No intersection, same length → both reach null on the same step → null. ✅
- No intersection, different lengths → both reach null after a + b steps. ✅
- Intersect at the heads → equal at step 0. ✅

## ⚠️ Pitfalls
- **Comparing values:** example 1 has a 1 in both lists that isn't shared. Compare nodes.
- **Switching with `pa = pa.next ? pa.next : headB`:** this skips the null step, and with no intersection it loops forever. Switch only after landing on null: `pa = pa ? pa.next : headB`.
- **Re-linking the lists** (e.g. joining A's tail to B to make a cycle and using LC 142) works, but you must undo it; the problem forbids changes.

## 🎯 What the Interviewer Wants
- O(1) space via alignment: either length difference or head switching.
- A proof that the switching version terminates when there's no intersection.
- Node identity, not values.

## Follow-ups
- **Turn it into cycle detection:** [LC 0142 Linked List Cycle II](../0142-linked-list-cycle-ii/)
- **Same trick with parent pointers in a tree:** LC 1650 Lowest Common Ancestor of a Binary Tree III (not added yet)
- **Plain cycle detection:** [LC 0141 Linked List Cycle](../0141-linked-list-cycle/)
