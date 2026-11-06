---
number: 117
title: Populating Next Right Pointers in Each Node II
difficulty: Medium
topic: Trees
pattern: Level linking with dummy
link: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
lists: [LC Top Interview 150]
followup_of: []
related: ["0116 Populating Next Right Pointers in Each Node", "0199 Binary Tree Right Side View", "0102 Binary Tree Level Order Traversal"]
---

# 0117. Populating Next Right Pointers in Each Node II

## ⚡ 30-Second Summary
**Pattern:** Walk a level through `next` pointers while building the next level's chain
**Key insight:** Once level k is linked, you can traverse it like a linked list. While walking it, append each child to a "next level" chain behind a dummy node. When the walk ends, dummy.next is the start of level k+1, already linked.
**Go-to:** Dummy-node level linking, O(n) time, O(1) extra space

## Problem
Each node has a `next` pointer, initially null. Point every node's `next` to the node immediately to its right on the same level (null for the last node). The tree is any binary tree (not necessarily perfect). [LeetCode](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/)

**Examples:**
```
Input:  root = [1,2,3,4,5,null,7]
Output: [1,#,2,3,#,4,5,7,#]
Why:    Output lists each level by following next pointers; # ends a level.
        5 links to 7 across the gap where 3's missing left child would be.

Input:  root = []
Output: []
Why:    Nothing to link.
```

**Constraints:**
- 0 ≤ n ≤ 6000.
- Follow-up: constant extra space (recursion stack doesn't count, but the dummy approach needs none).

## Hints
<details><summary>Hint 1</summary>
With a queue this is just level order: link each popped node to the next one in the same level. Can you avoid the queue?
</details>
<details><summary>Hint 2</summary>
If the current level is already linked via next, you can walk it without a queue.
</details>
<details><summary>Hint 3</summary>
For each level: dummy, tail = dummy; walk cur along next; append cur.left, cur.right to tail. Then cur = dummy.next for the next level.
</details>

## Clarifying Questions
- Perfect tree? (No, that's 0116. Any tree here.)
- Return the root? (Yes.)

## Example Walkthrough
Level [1]: append 2, 3 → chain 2 → 3. Level [2,3]: append 4, 5 (from 2), 7 (from 3) → 4 → 5 → 7. Level [4,5,7]: no children → done.

## Approaches

### 1. BFS Queue: O(n) time, O(w) space
Level-size loop; set `node.next = q.front()` for all but the last node of each level.

### 2. Dummy-Node Level Linking ⭐ Go-to: O(n) time, O(1) space
**Why it's the go-to:** meets the constant-space follow-up and handles missing children naturally.

## Dry Run (Approach 2)
`[1,2,3,4,5,null,7]`

| level walk | appended to chain | next level starts at |
|------------|-------------------|----------------------|
| 1 | 2, 3 | 2 |
| 2 → 3 | 4, 5, 7 | 4 |
| 4 → 5 → 7 | (none) | null → stop |

## Edge Case Check
- Empty tree: return null. ✅
- Gaps (missing children): only existing children get appended. ✅
- Single node: next stays null. ✅

## ⚠️ Pitfalls
- **Assuming a perfect tree** (`left.next = right; right.next = next.left`): breaks with gaps.
- **Not resetting the dummy's next** between levels: you'd loop forever on the same level.
- **Linking the last node of a level to the next level's first** in the BFS version.

## 🎯 What the Interviewer Wants
- Start with BFS, then reach O(1) space by reusing the next pointers.
- The dummy-node chain-building trick.

## Follow-ups
- **Perfect binary tree:** simpler O(1) linking: LC 0116 Populating Next Right Pointers in Each Node (not added yet)
- **Right side view:** the last node of each linked level: [LC 0199 Binary Tree Right Side View](../0199-binary-tree-right-side-view/)
