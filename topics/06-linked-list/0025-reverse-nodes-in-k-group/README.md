---
number: 25
title: Reverse Nodes in k-Group
difficulty: Hard
topic: Linked List
pattern: Group reversal with dummy
link: https://leetcode.com/problems/reverse-nodes-in-k-group/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0206 Reverse Linked List"]
related: ["0206 Reverse Linked List", "0092 Reverse Linked List II", "0024 Swap Nodes in Pairs"]
---

# 0025. Reverse Nodes in k-Group

## ⚡ 30-Second Summary
**Pattern:** Reverse fixed-size groups, stitched with a dummy and a `groupPrev` pointer
**Key insight:** For each group: check that k nodes exist (else stop: the tail stays as is), reverse exactly those k nodes with the 0206 loop (stopping at the node after the group), then reconnect: the node before the group now points to the old k-th node, and the old first node becomes the new `groupPrev`.
**Go-to:** Iterative group reversal, O(n) time, O(1) space

## Problem
Reverse the nodes of a linked list k at a time. If the number of nodes left at the end is less than k, leave them as they are. Only relink nodes; don't change values.

**Examples:**
```
Input:  head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
Why:    Groups (1,2) and (3,4) reverse; 5 is a short leftover.

Input:  head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
Why:    Group (1,2,3) reverses; (4,5) is shorter than 3, so it stays.
```

**Constraints:**
- 1 ≤ k ≤ n ≤ 5000.
- Follow-up: O(1) extra memory.

## Hints
<details><summary>Hint 1</summary>
You already know how to reverse a whole list. What changes when you only reverse k nodes and then continue?
</details>
<details><summary>Hint 2</summary>
Before reversing, find the k-th node from the current position. If it doesn't exist, you're done. What pointer do you need to keep so you can reconnect the reversed group?
</details>
<details><summary>Hint 3</summary>
Keep groupPrev (the node before the group). Find kth. Reverse from groupPrev.next up to kth.next, starting `prev` at kth.next so the reversed group links to the rest. Then groupPrev.next = kth, and groupPrev = the old first node.
</details>

## Clarifying Questions
- What happens to a final group shorter than k? (Left unchanged.)
- Can I swap values instead of nodes? (No.)
- k = 1? (The list is unchanged.)

## Example Walkthrough
`[1,2,3,4,5], k = 3`, dummy → 1 …
- groupPrev = dummy; kth = 3 exists. Reverse 1,2,3 with prev starting at 4: 3 → 2 → 1 → 4.
- dummy.next = 3; groupPrev = 1 (old first, now last of the group).
- From 1, the 3rd node ahead doesn't exist (only 4, 5): stop. Result [3,2,1,4,5].

## Approaches

### 1. Collect Values, Reverse Chunks, Rebuild: O(n) time, O(n) space
Copy values into an array, reverse each full chunk of k, and build a new list. Easy, but O(n) space and it doesn't relink the original nodes (violates the spirit of the problem).

### 2. Iterative Group Reversal ⭐ Go-to: O(n) time, O(1) space
Dummy node + groupPrev; check, reverse, reconnect, advance.
**Why it's the go-to:** meets the O(1)-memory follow-up and is just 0206 plus careful reconnection.

## Dry Run (Approach 2)
`[1,2,3,4,5], k = 2`

| group | groupPrev | kth | after reversal | reconnect | new groupPrev |
|-------|-----------|-----|----------------|-----------|---------------|
| 1 | dummy | 2 | 2 → 1 → 3 | dummy → 2 | 1 |
| 2 | 1 | 4 | 4 → 3 → 5 | 1 → 4 | 3 |
| 3 | 3 | none (only 5) | stop | | |
| result | | | | | **[2,1,4,3,5]** |

## Edge Case Check
- k = 1: each group is one node; nothing changes. ✅
- k = n: one full reversal. ✅
- n a multiple of k: every group reverses; loop ends when the k-th lookup hits null. ✅

## ⚠️ Pitfalls
- **Reversing the short tail**: always check that k nodes exist first.
- **Starting `prev` at null** inside the group: the reversed group would end in null and lose the rest of the list. Start `prev` at `kth.next`.
- **Advancing groupPrev to kth** instead of the old first node: the old first node is the group's new last node.
- **Losing the old first node**: save `groupPrev.next` before rewiring.

## 🎯 What the Interviewer Wants
- A clear plan: check → reverse → reconnect → advance, before writing code.
- Correct pointer bookkeeping with a dummy, no special case for the first group.
- O(1) extra space.

## Follow-ups
- **k = 2 specifically:** LC 0024 Swap Nodes in Pairs (not added yet)
- **Reverse one range:** [LC 0092 Reverse Linked List II](../0092-reverse-linked-list-ii/)
- **Reverse the leftover group too:** drop the existence check (reverse min(k, remaining)).
- **Recursive version:** reverse the first k, then `first.next = reverseKGroup(rest, k)`; O(n/k) stack.
