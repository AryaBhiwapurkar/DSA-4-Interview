---
number: 24
title: Swap Nodes in Pairs
difficulty: Medium
topic: Linked List
pattern: Dummy head + pointer rewiring in pairs
link: https://leetcode.com/problems/swap-nodes-in-pairs/
lists: [Interview Extras]
followup_of: []
related: ["0025 Reverse Nodes in k-Group", "0206 Reverse Linked List", "0092 Reverse Linked List II"]
---

# 0024. Swap Nodes in Pairs

## ⚡ 30-Second Summary
**Pattern:** Dummy node + three pointer updates per pair
**Key insight:** `prev` points at the node before the pair (a, b). Rewire `a.next = b.next`, `b.next = a`, `prev.next = b`; then a is the node before the next pair. A dummy head means the first pair needs no special case.
**Go-to:** Iterative rewiring with a dummy, O(n) time, O(1) space

## Problem
Swap every two adjacent nodes of a linked list and return the new head. Change the links, not the values. A leftover last node stays put. [LeetCode](https://leetcode.com/problems/swap-nodes-in-pairs/)

**Examples:**
```
Input:  head = [1,2,3,4]
Output: [2,1,4,3]
Why:    (1,2) and (3,4) each swap.

Input:  head = []
Output: []
Why:    Nothing to swap.

Input:  head = [1]
Output: [1]
Why:    A single node has no partner.

Input:  head = [1,2,3]
Output: [2,1,3]
Why:    (1,2) swaps; 3 is left alone.
```

**Constraints:**
- 0 ≤ n ≤ 100. Values must not be modified: only links.

## Hints
<details><summary>Hint 1</summary>
Focus on one pair (a, b) and the node before it. Which pointers have to change?
</details>
<details><summary>Hint 2</summary>
Three of them: the node before must point at b, b must point at a, a must point at whatever came after b. What plays "the node before" for the first pair?
</details>
<details><summary>Hint 3</summary>
A dummy node. Loop while prev.next and prev.next.next exist; after rewiring, the new prev is a.
</details>

## Clarifying Questions
- May I swap values instead of nodes? (No.)
- Odd length: is the last node left alone? (Yes.)
- Empty list? (Return empty.)

## Example Walkthrough
`dummy → 1 → 2 → 3 → 4`. Pair (1, 2): 1 → 3, 2 → 1, dummy → 2, giving `dummy → 2 → 1 → 3 → 4`, prev = 1. Pair (3, 4): 3 → null, 4 → 3, 1 → 4, giving `2 → 1 → 4 → 3`.

## Approaches

### 1. Recursion: O(n) time, O(n) stack
`second = head.next; head.next = swap(second.next); second.next = head; return second`. Elegant; uses n/2 stack frames.

### 2. Iterative with a Dummy ⭐ Go-to: O(n) time, O(1) space
Three assignments per pair, with prev moving two nodes each time.
**Why it's the go-to:** constant space, and the dummy removes the head special case.

## Dry Run (Approach 2)
`[1,2,3,4,5]`

| prev | a | b | after rewiring |
|------|---|---|----------------|
| dummy | 1 | 2 | dummy → 2 → 1 → 3 → 4 → 5 |
| 1 | 3 | 4 | … 2 → 1 → 4 → 3 → 5 |
| 3 | 5 | null | loop stops (no pair) → **[2,1,4,3,5]** |

## Edge Case Check
- Empty or one node → loop never runs; return dummy.next. ✅
- Odd length → the last node stays attached via `a.next = b.next`. ✅

## ⚠️ Pitfalls
- **Wrong assignment order:** do `a.next = b.next` before `b.next = a`, or you lose the rest of the list.
- **Forgetting `prev.next = b`:** the previous pair still points at a.
- **Swapping values** is explicitly disallowed (and doesn't generalise to k-group).

## 🎯 What the Interviewer Wants
- Clean pointer manipulation with a dummy head.
- The right assignment order, explained.
- Mention the generalisation to k-group reversal.

## Follow-ups
- **Reverse every k nodes:** [LC 0025 Reverse Nodes in k-Group](../0025-reverse-nodes-in-k-group/)
- **Reverse a whole list:** [LC 0206 Reverse Linked List](../0206-reverse-linked-list/)
- **Reverse a sub-range:** [LC 0092 Reverse Linked List II](../0092-reverse-linked-list-ii/)
