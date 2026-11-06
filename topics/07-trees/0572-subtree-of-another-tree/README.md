---
number: 572
title: Subtree of Another Tree
difficulty: Easy
topic: Trees
pattern: DFS + same-tree check
link: https://leetcode.com/problems/subtree-of-another-tree/
lists: [NeetCode 150]
followup_of: ["0100 Same Tree"]
related: ["0100 Same Tree", "0652 Find Duplicate Subtrees", "0028 Find the Index of the First Occurrence in a String"]
---

# 0572. Subtree of Another Tree

## ⚡ 30-Second Summary
**Pattern:** DFS over `root`, Same Tree check at each node
**Key insight:** `subRoot` is a subtree of `root` iff it's identical to the subtree rooted at some node. Try every node as a starting point with the 0100 check.
**Go-to:** DFS + isSameTree, O(m·n) time, O(h) space

## Problem
Return whether `subRoot` appears in `root` as a complete subtree: some node of `root` together with all of its descendants is identical to `subRoot`. [LeetCode](https://leetcode.com/problems/subtree-of-another-tree/)

**Examples:**
```
Input:  root = [3,4,5,1,2], subRoot = [4,1,2]
Output: true
Why:    The node 4 with children 1, 2 matches exactly.

Input:  root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
Output: false
Why:    Node 2 has an extra child 0, so the subtree at 4 isn't identical.
```

**Constraints:**
- root has 1..2000 nodes, subRoot has 1..1000, so O(m·n) ≈ 2·10⁶ is fine.

## Hints
<details><summary>Hint 1</summary>
If you had isSameTree, how would you use it here?
</details>
<details><summary>Hint 2</summary>
Check the current node, then recurse into the left and right subtrees of `root`.
</details>
<details><summary>Hint 3</summary>
isSubtree(r, s) = r != null && (same(r, s) || isSubtree(r.left, s) || isSubtree(r.right, s)). For O(m + n), serialize both with null markers and delimiters and do a substring search.
</details>

## Clarifying Questions
- Must the whole subtree match, including leaves below? (Yes, a full copy.)
- Duplicate values? (Yes, that's why every node must be tried.)

## Example Walkthrough
Example 2: at node 4, compare with [4,1,2]: 4 = 4, 1 = 1, 2 = 2, but root's 2 has a left child 0 and subRoot's 2 doesn't → not same. No other node has value 4 → false.

## Approaches

### 1. DFS + Same Tree ⭐ Go-to: O(m·n) time, O(h) space
Try each node of `root`.
**Why it's the go-to:** obviously correct, reuses 0100, fast enough for the limits.

### 2. Serialize + Substring Search: O(m + n) time with KMP, O(m + n) space
Preorder strings with null markers and value delimiters (e.g. `,4,1,#,#,2,#,#`), then check if subRoot's string is a substring of root's.

## Dry Run (Approach 1)
`root = [3,4,5,1,2]`, `subRoot = [4,1,2]`

| node | same(node, subRoot)? | action |
|------|----------------------|--------|
| 3 | 3 ≠ 4 | try children |
| 4 | 4,1,2 match | **true** |

## Edge Case Check
- subRoot equals root: matches at the root. ✅
- Values like 12 vs 2 in the serialize approach: the leading delimiter prevents ",2" matching inside ",12". ✅
- Extra descendants below a match (example 2): Same Tree rejects. ✅

## ⚠️ Pitfalls
- **Serializing without null markers**: different shapes collide.
- **Serializing without a leading delimiter**: "2,#,#" matches inside "12,#,#".
- **Using `&&` instead of `||`** across the three options.

## 🎯 What the Interviewer Wants
- Reuse Same Tree cleanly.
- State O(m·n) and know the O(m + n) serialize + KMP improvement.

## Follow-ups
- **Find all duplicate subtrees:** serialize each subtree into a hashmap: LC 0652 Find Duplicate Subtrees (not added yet)
- **Substring search in linear time:** [LC 0028 Find the Index of the First Occurrence in a String](../../01-arrays-hashing/0028-find-the-index-of-the-first-occurrence-in-a-string/)
- **Merkle hashing:** hash each subtree bottom-up and compare hashes.
