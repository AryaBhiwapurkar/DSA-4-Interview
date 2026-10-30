---
number: 92
title: Reverse Linked List II
difficulty: Medium
topic: Linked List
pattern: Sublist reversal
link: https://leetcode.com/problems/reverse-linked-list-ii/
lists: [LC Top Interview 150]
followup_of: ["0206 Reverse Linked List"]
related: ["0206 Reverse Linked List", "0025 Reverse Nodes in k-Group"]
---

# 0092. Reverse Linked List II

## ⚡ 30-Second Summary
**Pattern:** Sublist reversal by head insertion
**Key insight:** Stop at the node just before position `left` (`prev`). The node at `left` (`curr`) will end up last in the reversed range, so repeatedly take the node right after `curr` and move it to the front, right after `prev`. Do that `right - left` times.
**Go-to:** One pass with a dummy and head insertion, O(n) time, O(1) space

## Problem
Given a list and positions left ≤ right (1-indexed), reverse the nodes from position left to position right and return the head. One pass is the follow-up.

**Examples:**
```
Input:  head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Why:    Positions 2..4 hold 2,3,4; they reverse to 4,3,2.

Input:  head = [5], left = 1, right = 1
Output: [5]
Why:    A one-node range doesn't change anything.
```

**Constraints:**
- 1 ≤ n ≤ 500; 1 ≤ left ≤ right ≤ n.
- Follow-up: one pass.

## Hints
<details><summary>Hint 1</summary>
Which node do you need a pointer to so you can reconnect the reversed part to the front?
</details>
<details><summary>Hint 2</summary>
left can be 1, meaning the head changes. What trick makes that a normal case?
</details>
<details><summary>Hint 3</summary>
Dummy → prev at position left - 1, curr = prev.next. Repeat right - left times: move curr.next to right after prev.
</details>

## Clarifying Questions
- 1-indexed positions? (Yes.)
- Can left == right? (Yes: no change.)
- Can left be 1? (Yes: the head changes, so use a dummy.)

## Example Walkthrough
`[1,2,3,4,5], left 2, right 4`: prev = 1, curr = 2.
- Move 3 to the front: 1 → 3 → 2 → 4 → 5.
- Move 4 to the front: 1 → 4 → 3 → 2 → 5. Done (2 moves = right - left).

## Approaches

### 1. Collect Values, Reverse Segment, Rebuild: O(n) time, O(n) space
Copy values to an array, reverse the [left-1, right-1] slice, build a new list. Simple, but extra space and new nodes.

### 2. Head Insertion With a Dummy ⭐ Go-to: O(n) time, O(1) space
One pass to reach `prev`, then right - left pointer moves.
**Why it's the go-to:** single pass, O(1) space, and the dummy covers left = 1. (Alternative: cut out the sublist, reverse it with 0206, reconnect both ends.)

## Dry Run (Approach 2)
`[1,2,3,4,5], left 2, right 4` (prev = 1, curr = 2 stay fixed)

| move | nxt = curr.next | curr.next = nxt.next | nxt.next = prev.next | prev.next = nxt | list |
|------|-----------------|----------------------|----------------------|-----------------|------|
| 1 | 3 | 2 → 4 | 3 → 2 | 1 → 3 | 1,3,2,4,5 |
| 2 | 4 | 2 → 5 | 4 → 3 | 1 → 4 | **1,4,3,2,5** |

## Edge Case Check
- left == right: zero moves. ✅
- left = 1: prev is the dummy; return dummy.next (the new head). ✅
- right = n: curr ends as the tail, curr.next = null after the last move. ✅

## ⚠️ Pitfalls
- **Returning `head`** when left = 1: the head moved. Return dummy.next.
- **Moving `curr` during the loop**: in head insertion, curr stays put; only its next changes.
- **Off-by-one walking to prev**: walk left - 1 steps from the dummy.

## 🎯 What the Interviewer Wants
- One pass and O(1) space.
- Clear reasoning about which pointers stay fixed (prev, curr) and which move.
- The dummy node for left = 1.

## Follow-ups
- **Reverse the whole list:** [LC 0206 Reverse Linked List](../0206-reverse-linked-list/)
- **Reverse every k-block:** [LC 0025 Reverse Nodes in k-Group](../0025-reverse-nodes-in-k-group/)
- **Reverse alternate k-blocks:** same reversal, skip k nodes between groups.
