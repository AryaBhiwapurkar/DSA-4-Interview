---
number: 430
title: Flatten a Multilevel Doubly Linked List
difficulty: Medium
topic: Linked List
pattern: Splice each child list in place (or DFS that returns the tail)
link: https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/
lists: [Interview Extras]
followup_of: []
related: ["0114 Flatten Binary Tree to Linked List", "0341 Flatten Nested List Iterator", "0138 Copy List with Random Pointer"]
---

# 0430. Flatten a Multilevel Doubly Linked List

## ⚡ 30-Second Summary
**Pattern:** Pre-order flatten: child list goes between a node and its next
**Key insight:** Walk the top level. At a node with a child, find the child list's tail, then splice: `node → child … tail → old next`. Fix all four prev/next pointers and clear `node.child`, then keep walking. Nested children get handled as the walk reaches them. Each level's tail is searched once, so the total is O(n).
**Go-to:** Iterative splice, O(n) time, O(1) space

## Problem
Each node of a doubly linked list has `prev`, `next` and a `child` pointer. The child may point to another such list, and so on for any depth. Flatten everything into one level: each child list goes right after its parent and before the parent's old next. Set every `child` to null. [LeetCode](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/)

**Examples:**
```
Input:  head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
Output: [1,2,3,7,8,11,12,9,10,4,5,6]
Why:    3's child list 7-8-9-10 goes after 3; inside it, 8's child list 11-12 goes after 8.

Input:  head = [1,2,null,3]
Output: [1,3,2]
Why:    1's child 3 goes between 1 and 2.

Input:  head = []
Output: []
Why:    Nothing to flatten.
```
(LeetCode's input format lists each level, with nulls marking which node of the previous level holds the child.)

**Constraints:**
- 0 ≤ nodes ≤ 1000.

## Hints
<details><summary>Hint 1</summary>
The result is a pre-order traversal: node, then its whole child structure, then its next. Which tree problem does that resemble?
</details>
<details><summary>Hint 2</summary>
To splice a child list between node and node.next, you need the child list's last node. How do you find it, and which pointers change?
</details>
<details><summary>Hint 3</summary>
At a node with a child: walk to the child list's tail, set tail.next = node.next (and that node's prev = tail), node.next = child, child.prev = node, node.child = null. Then move to node.next and continue.
</details>

## Clarifying Questions
- Must `child` be null on every node afterwards? (Yes.)
- Must `prev` pointers be correct too? (Yes: it's a doubly linked list.)
- Can a child list itself have children at any depth? (Yes.)

## Example Walkthrough
Example 1: walk 1, 2, 3. Node 3 has child 7; its level's tail is 10. Splice to get 1-2-3-7-8-9-10-4-5-6. Continue to 7, then 8: child 11, tail 12. Splice to get …8-11-12-9-10-4-5-6. No more children.

## Approaches

### 1. Collect in Pre-order, then Relink: O(n) time, O(n) space
DFS with a stack (push next, then child) to list the nodes in final order. Then rewrite every prev/next and clear the children. Simple, but uses an array.

### 2. Recursive DFS Returning the Tail: O(n) time, O(depth) stack
`flatten(node)` flattens one level and returns its last node. At a child, flatten the child, splice it in between the node and its old next, and continue. A common interview answer.

### 3. Iterative Splice ⭐ Go-to: O(n) time, O(1) space
Splice each child list into place as soon as the walk reaches it.
**Why it's the go-to:** no recursion, no extra memory, and the four pointer updates are easy to explain.

## Dry Run (Approach 3)
Example 1.

| cur | child? | tail of child level | list after splice |
|-----|--------|---------------------|-------------------|
| 1, 2 | no | | 1-2-3-4-5-6 |
| 3 | 7 | 10 | 1-2-3-7-8-9-10-4-5-6 |
| 7 | no | | |
| 8 | 11 | 12 | 1-2-3-7-8-11-12-9-10-4-5-6 |
| 11 … 6 | no | | **final** |

## Edge Case Check
- Empty list → null. ✅
- Child on the last node → the tail's next is null; skip the `prev` fix. ✅
- A chain of single-node children (1 → child 2 → child 3) → each splice is one node; the order is 1, 2, 3. ✅

## ⚠️ Pitfalls
- **Forgetting `prev` links:** set both `child.prev = node` and `oldNext.prev = tail`.
- **Leaving `node.child` set:** the checker requires every child to be null.
- **Null `next` when the node is last:** guard before setting `oldNext.prev`.

## 🎯 What the Interviewer Wants
- See the pre-order structure (it's flattening a tree).
- Correct four-pointer splice on a doubly linked list.
- The O(n) argument (each level's tail is found once) and the O(1)-space version.

## Follow-ups
- **The same splice on a binary tree:** [LC 0114 Flatten Binary Tree to Linked List](../../07-trees/0114-flatten-binary-tree-to-linked-list/)
- **Flatten lazily with an iterator:** LC 0341 Flatten Nested List Iterator (not added yet)
- **Another extra-pointer list problem:** [LC 0138 Copy List with Random Pointer](../0138-copy-list-with-random-pointer/)
