---
number: 141
title: Linked List Cycle
difficulty: Easy
topic: Linked List
pattern: Floyd fast/slow
link: https://leetcode.com/problems/linked-list-cycle/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0142 Linked List Cycle II", "0287 Find the Duplicate Number", "0202 Happy Number", "0876 Middle of the Linked List"]
---

# 0141. Linked List Cycle

## ⚡ 30-Second Summary
**Pattern:** Floyd's tortoise and hare
**Key insight:** Move one pointer 1 step and another 2 steps. Without a cycle the fast one reaches null. With a cycle both end up circling it, and the gap between them shrinks by 1 every step, so they must meet.
**Go-to:** Fast/slow pointers, O(n) time, O(1) space

## Problem
Given the head of a linked list, return whether some node can be reached again by following `next` pointers (i.e., the list has a cycle). The `pos` in the examples only describes where the tail links back; it isn't passed to the function.

**Examples:**
```
Input:  head = [3,2,0,-4], pos = 1
Output: true
Why:    The tail (-4) links back to the node at index 1 (value 2).

Input:  head = [1,2], pos = 0
Output: true
Why:    The tail links back to the head.

Input:  head = [1], pos = -1
Output: false
Why:    pos -1 means no cycle.
```

**Constraints:**
- 0 ≤ n ≤ 10⁴ (empty list allowed).
- Follow-up: O(1) memory.

## Hints
<details><summary>Hint 1</summary>
The obvious way is to remember every node you've seen. What does that cost?
</details>
<details><summary>Hint 2</summary>
On a circular track, a faster runner eventually laps a slower one. Can two pointers play those roles?
</details>
<details><summary>Hint 3</summary>
slow = fast = head. While fast and fast.next exist: slow 1 step, fast 2 steps; if they're the same node, return true. Exit the loop → false.
</details>

## Clarifying Questions
- Is pos given to the function? (No, only the head.)
- Can values repeat? (Yes, so compare node identity, never values.)
- Can I modify the list? (Shouldn't; marking visited nodes destroys the input.)

## Example Walkthrough
`[3,2,0,-4]`, tail → node 2
- slow 3, fast 3. Step: slow 2, fast 0. Step: slow 0, fast 2 (0 → -4 → 2). Step: slow -4, fast -4 (2 → 0 → -4). Same node → true.

## Approaches

### 1. Hash Set of Visited Nodes: O(n) time, O(n) space
Store node pointers; seeing one twice means a cycle.

### 2. Floyd Fast/Slow ⭐ Go-to: O(n) time, O(1) space
Fast moves 2, slow moves 1; meeting means a cycle, null means none.
**Why it's the go-to:** O(1) memory as the follow-up asks, and the same trick solves 0142, 0287, 0876, 0202.

## Dry Run (Approach 2)
`[1,2]`, tail → head

| step | slow | fast | same? |
|------|------|------|-------|
| 0 | 1 | 1 | (start, don't check) |
| 1 | 2 | 1 (1→2→1) | no |
| 2 | 1 | 1 (1→2→1) | **yes → true** |

## Edge Case Check
- Empty list: `fast` is null, loop skipped, false. ✅
- Single node, no cycle: fast.next is null, false. ✅
- Single node pointing to itself: slow and fast both return to it after one step, true. ✅

## ⚠️ Pitfalls
- **Checking `slow == fast` before moving**: they start equal, so you'd always return true.
- **Checking only `fast` or only `fast.next`**: need both before `fast.next.next`.
- **Comparing values instead of nodes**: duplicates give false positives.
- **Python: `slow == fast`** compares identity by default for plain classes, but `is` is clearer.

## 🎯 What the Interviewer Wants
- Hash set first, then the O(1) improvement.
- Explain why they must meet (gap shrinks by 1 per step inside the cycle).
- Be ready for "where does the cycle start?" (0142).

## Follow-ups
- **Return the cycle's start node:** after meeting, restart one pointer at head and move both 1 step; they meet at the entry: LC 0142 Linked List Cycle II (not added yet)
- **Array values as next pointers:** [LC 0287 Find the Duplicate Number](../0287-find-the-duplicate-number/)
- **Middle node:** stop when fast hits the end: LC 0876 Middle of the Linked List (not added yet)
- **Cycle in a number sequence:** LC 0202 Happy Number (not added yet)
- **Cycle length:** after meeting, keep one still and count steps until the other comes back.
