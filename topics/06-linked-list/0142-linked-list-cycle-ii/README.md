---
number: 142
title: Linked List Cycle II
difficulty: Medium
topic: Linked List
pattern: Floyd's cycle detection, phase 2 (find the entry)
link: https://leetcode.com/problems/linked-list-cycle-ii/
lists: [Interview Extras]
followup_of: ["0141 Linked List Cycle"]
related: ["0141 Linked List Cycle", "0287 Find the Duplicate Number", "0202 Happy Number"]
---

# 0142. Linked List Cycle II

## ⚡ 30-Second Summary
**Pattern:** Fast/slow pointers, then a second walk at equal speed
**Key insight:** Let a = steps from head to the cycle entry, b = steps from entry to where slow and fast meet, c = cycle length. Fast walked twice as far as slow: 2(a + b) = a + b + k·c, so a = k·c − b. Starting one pointer at head and one at the meeting point, both moving one step at a time, they meet exactly at the entry.
**Go-to:** Floyd's two phases, O(n) time, O(1) space

## Problem
Return the node where a linked list's cycle begins, or null if there is no cycle. Don't modify the list. [LeetCode](https://leetcode.com/problems/linked-list-cycle-ii/)

**Examples:**
```
Input:  head = [3,2,0,-4], pos = 1
Output: the node at index 1 (value 2)
Why:    The tail -4 links back to 2, so that's where the loop starts.

Input:  head = [1,2], pos = 0
Output: the node at index 0 (value 1)
Why:    2 links back to 1.

Input:  head = [1], pos = -1
Output: null
Why:    The single node points to nothing.
```

**Constraints:**
- 0 ≤ n ≤ 10⁴; `pos` only describes the test, it isn't passed in.
- Follow-up: O(1) extra memory.

## Hints
<details><summary>Hint 1</summary>
LC 141's fast/slow pointers tell you whether there's a cycle. Where do they meet, relative to the entry?
</details>
<details><summary>Hint 2</summary>
Write the distances: head → entry = a, entry → meeting point = b, cycle length = c. Fast has walked twice as far as slow. What equation follows?
</details>
<details><summary>Hint 3</summary>
a ≡ c − b (mod c): walking a steps from the meeting point lands on the entry. Reset one pointer to head and step both by one until they meet.
</details>

## Clarifying Questions
- Return the node itself (not its index or value)? (The node.)
- Can I modify the list, e.g. mark visited nodes? (No.)
- Can the list be empty? (Yes → null.)

## Example Walkthrough
`[3,2,0,-4], pos = 1`. Indices 0..3, and node 3 links back to node 1. Phase 1: slow 0→1→2→3, fast 0→2→1→3, so they meet at node 3. Phase 2: p from head, q from node 3: p 0→1, q 3→1. They meet at node 1, the entry.

## Approaches

### 1. Hash Set of Visited Nodes: O(n) time, O(n) space
Walk the list; the first node seen twice is the entry.

### 2. Floyd's Two Phases ⭐ Go-to: O(n) time, O(1) space
Phase 1 finds a meeting point inside the cycle; phase 2 walks from head and from the meeting point at equal speed.
**Why it's the go-to:** it meets the O(1)-space follow-up, and the a = k·c − b argument is short enough to say at the whiteboard.

## Dry Run (Approach 2)
`[1,2,3,4,5,6], pos = 2` (indices 0..5, and node 5 links back to node 2): a = 2, c = 4.

| step | slow | fast | note |
|------|------|------|------|
| 0 | 0 | 0 | start |
| 1 | 1 | 2 | |
| 2 | 2 | 4 | |
| 3 | 3 | 2 | 4→5→2 |
| 4 | 4 | 4 | **meet** at node 4 (b = 2) |
| phase 2 | p = 0, q = 4 | | |
| 1 | p = 1 | q = 5 | |
| 2 | p = 2 | q = 2 | **entry = node 2** ✅ (a = 2 = c − b) |

## Edge Case Check
- Empty list or one node without a loop → phase 1 exits → null. ✅
- Self-loop `[1], pos 0` → they meet at node 0; phase 2 returns it immediately. ✅
- Cycle through the whole list (pos = 0) → a = 0, so the meeting point is the entry. ✅

## ⚠️ Pitfalls
- **Checking `slow == fast` before moving:** both start at head, so it is true at once.
- **Restarting both pointers at head in phase 2:** only one goes back to head; the other stays at the meeting point.
- **Comparing values instead of nodes:** values can repeat. Compare pointers (`is` in Python).

## 🎯 What the Interviewer Wants
- Phase 1 from LC 141, plus the distance argument for phase 2.
- O(1) space without mutating the list.
- Recognise the same trick in LC 287 (array as a linked list).

## Follow-ups
- **Just detect the cycle:** [LC 0141 Linked List Cycle](../0141-linked-list-cycle/)
- **Duplicate in an array via cycle entry:** [LC 0287 Find the Duplicate Number](../0287-find-the-duplicate-number/)
- **Cycle detection on a number sequence:** [LC 0202 Happy Number](../../17-math-geometry/0202-happy-number/)
