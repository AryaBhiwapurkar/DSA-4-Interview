---
number: 297
title: Serialize and Deserialize Binary Tree
difficulty: Hard
topic: Trees
pattern: Preorder with null markers
link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
lists: [NeetCode 150]
followup_of: []
related: ["0449 Serialize and Deserialize BST", "0105 Construct Binary Tree from Preorder and Inorder Traversal", "0572 Subtree of Another Tree"]
---

# 0297. Serialize and Deserialize Binary Tree

## ⚡ 30-Second Summary
**Pattern:** Preorder traversal with explicit null markers
**Key insight:** One traversal is ambiguous, but one traversal **plus null markers** fully determines the shape. Write preorder with `#` for each null child; to read it back, consume tokens in the same preorder: a value creates a node and recursively reads its left then right; `#` returns null.
**Go-to:** Preorder + `#` markers, O(n) time, O(n) space

## Problem
Design `serialize(root) → string` and `deserialize(string) → root` so that deserializing a serialized tree gives back an identical tree. The format is up to you. [LeetCode](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

**Examples:**
```
Input:  root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
Why:    Whatever the string format, the round trip must rebuild the same tree.

Input:  root = []
Output: []
Why:    The empty tree must round-trip too.
```

**Constraints:**
- 0 ≤ n ≤ 10⁴; values in ±1000 (negative, multi-digit), so use a delimiter.

## Hints
<details><summary>Hint 1</summary>
Why isn't a plain preorder list enough to rebuild a tree?
</details>
<details><summary>Hint 2</summary>
What if every missing child were written down explicitly?
</details>
<details><summary>Hint 3</summary>
Serialize: preorder, writing "#" for null, comma-separated. Deserialize: an iterator over tokens; read a token; if "#", return null; else make a node, read its left subtree, then its right.
</details>

## Clarifying Questions
- Any format allowed? (Yes, as long as it round-trips.)
- Negative / multi-digit values? (Yes: use delimiters.)
- Can I use globals / static state? (No: the codec must be stateless between calls.)

## Example Walkthrough
`[1,2,3,null,null,4,5]` → preorder with markers: `1,2,#,#,3,4,#,#,5,#,#`.
Reading back: 1 → left: 2 → left # → right # → right of 1: 3 → left 4 (#, #) → right 5 (#, #).

## Approaches

### 1. Preorder With Null Markers ⭐ Go-to: O(n) time, O(n) space
**Why it's the go-to:** the encoder and decoder are mirror-image recursions, so they're easy to get right.

### 2. BFS Level Order With Null Markers: O(n) time, O(n) space
The LeetCode format. Decode by reading children pairs for each queued node. Iterative, so no recursion-depth concerns on skewed trees.

## Dry Run (Approach 1, decoding)
tokens `1,2,#,#,3,4,#,#,5,#,#`

| token | action | stack of pending nodes |
|-------|--------|------------------------|
| 1 | new node 1, read left | 1 |
| 2 | new node 2 (1.left), read left | 1, 2 |
| # | 2.left = null, read 2.right | 1, 2 |
| # | 2.right = null, done with 2 | 1 |
| 3 | 1.right = 3, read left | 1, 3 |
| 4, #, # | 3.left = 4 (leaf) | 1, 3 |
| 5, #, # | 3.right = 5 (leaf) | done |

## Edge Case Check
- Empty tree: serialize as "#", deserialize "#" → null. ✅
- Negative values `[1,-2,3]`: delimiter keeps "-2" intact. ✅
- Skewed 10⁴-deep tree: recursion depth 10⁴; fine in C++/Go, use BFS in Python. ✅

## ⚠️ Pitfalls
- **No null markers**: shapes become ambiguous.
- **No delimiter**: "12" vs "1","2" can't be told apart.
- **Shared mutable index as a global**: breaks if the codec is reused. Keep it local to each call.
- **Python string concatenation in a loop**: build a list and join.

## 🎯 What the Interviewer Wants
- Explain why null markers make one traversal sufficient.
- Clean, symmetric encode/decode.
- Discuss trade-offs: preorder (recursive, compact) vs. BFS (iterative, LeetCode-style).

## Follow-ups
- **BST only, more compact:** preorder without markers, use bounds to decode: LC 0449 Serialize and Deserialize BST (not added yet)
- **Rebuild from two traversals instead:** [LC 0105 Construct Binary Tree from Preorder and Inorder Traversal](../0105-construct-binary-tree-from-preorder-and-inorder-traversal/)
- **Compare subtrees by serialization:** [LC 0572 Subtree of Another Tree](../0572-subtree-of-another-tree/)
