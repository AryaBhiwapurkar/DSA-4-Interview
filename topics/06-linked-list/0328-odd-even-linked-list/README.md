---
number: 328
title: Odd Even Linked List
difficulty: Medium
topic: Linked List
pattern: Split into two chains in place, then join
link: https://leetcode.com/problems/odd-even-linked-list/
lists: [Interview Extras]
followup_of: []
related: ["0086 Partition List", "0143 Reorder List", "0725 Split Linked List in Parts"]
---

# 0328. Odd Even Linked List

## ⚡ 30-Second Summary
**Pattern:** Two tails (odd and even) that leapfrog each other
**Key insight:** Odd and even positions alternate, so `odd.next = even.next` and `even.next = odd.next` (after odd moves) peel off the two chains in one pass. Remember the even head and attach it after the last odd node.
**Go-to:** In-place two chains, O(n) time, O(1) space

## Problem
Reorder a linked list so that all nodes at odd positions (1st, 3rd, …) come first, then all nodes at even positions, keeping the relative order inside each group. Use O(1) extra space and O(n) time. Positions count from 1, regardless of values. [LeetCode](https://leetcode.com/problems/odd-even-linked-list/)

**Examples:**
```
Input:  head = [1,2,3,4,5]
Output: [1,3,5,2,4]
Why:    Positions 1, 3, 5 hold 1, 3, 5; positions 2, 4 hold 2, 4.

Input:  head = [2,1,3,5,6,4,7]
Output: [2,3,6,7,1,5,4]
Why:    Grouping is by position, not by value: positions 1,3,5,7 hold 2,3,6,7.
```

**Constraints:**
- 0 ≤ n ≤ 10⁴. O(1) extra space required.

## Hints
<details><summary>Hint 1</summary>
Imagine building two separate lists, one from the odd positions and one from the even positions. How would you join them?
</details>
<details><summary>Hint 2</summary>
You don't need new nodes: keep a tail for each chain and relink as you go. What should each tail point to next?
</details>
<details><summary>Hint 3</summary>
odd = head, even = head.next, evenHead = even. While even and even.next: odd.next = even.next, odd = odd.next, even.next = odd.next, even = even.next. Finally odd.next = evenHead.
</details>

## Clarifying Questions
- Odd/even by position or by value? (Position, 1-indexed.)
- Keep relative order inside each group? (Yes.)
- Empty or single-node list? (Return as is.)

## Example Walkthrough
`[1,2,3,4,5]`: odd chain 1 → 3 → 5, even chain 2 → 4. Join: 1 → 3 → 5 → 2 → 4.

## Approaches

### 1. Collect Nodes into Two Arrays: O(n) time, O(n) space
Push odd-position nodes and even-position nodes into two arrays, then relink them in order. Easy, but O(n) space breaks the requirement.

### 2. In-place Two Chains ⭐ Go-to: O(n) time, O(1) space
Leapfrog the two tails through the list, then attach the even head.
**Why it's the go-to:** meets the O(1)-space requirement in about six lines.

## Dry Run (Approach 2)
`[1,2,3,4,5]`, odd = 1, even = 2, evenHead = 2.

| step | odd.next = even.next | odd | even.next = odd.next | even |
|------|----------------------|-----|----------------------|------|
| 1 | 1 → 3 | 3 | 2 → 4 | 4 |
| 2 | 3 → 5 | 5 | 4 → null | null |
| end | even is null: stop; 5 → evenHead (2) | | | **[1,3,5,2,4]** |

## Edge Case Check
- Empty → return null. ✅
- One or two nodes → loop doesn't run; odd.next = evenHead keeps the order. ✅
- Even length → `even.next` becomes null at the end, so the list terminates. ✅

## ⚠️ Pitfalls
- **Loop condition:** `even && even.next`. Checking only `odd.next` dereferences null on even lengths.
- **Losing the even head:** save it before you start relinking.
- **Grouping by value parity:** the problem is about positions.

## 🎯 What the Interviewer Wants
- In-place relinking with two tails.
- A correct stop condition for both odd and even lengths.
- O(1) extra space.

## Follow-ups
- **Split by value (< x and ≥ x) instead of position:** [LC 0086 Partition List](../0086-partition-list/)
- **Interleave halves instead of separating:** [LC 0143 Reorder List](../0143-reorder-list/)
- **Split into k parts:** LC 0725 Split Linked List in Parts (not added yet)
