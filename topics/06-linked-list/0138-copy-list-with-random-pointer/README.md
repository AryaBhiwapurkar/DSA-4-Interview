---
number: 138
title: Copy List with Random Pointer
difficulty: Medium
topic: Linked List
pattern: Hashmap old→new / interleave
link: https://leetcode.com/problems/copy-list-with-random-pointer/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0133 Clone Graph", "1485 Clone Binary Tree With Random Pointer"]
---

# 0138. Copy List with Random Pointer

## ⚡ 30-Second Summary
**Pattern:** Hashmap from original node to its copy
**Key insight:** A `random` pointer can point forward to a node you haven't copied yet. So do two passes: first create every copy and remember `old → new`, then wire `next` and `random` by looking up the map.
**Go-to:** Two-pass hashmap, O(n) time, O(n) space

## Problem
Each node has `next` and an extra `random` pointer (to any node or null). Return a deep copy: all new nodes, with the copies' `next` and `random` pointing at copies, never at original nodes. The examples show each node as [val, index of random node or null].

**Examples:**
```
Input:  head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Why:    Same shape, all new nodes; e.g. 11's random still points to the 5th node.

Input:  head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Why:    Both randoms point to the second node, including the node's own pointer.

Input:  head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
Why:    Duplicate values: identity, not values, defines the structure.
```

**Constraints:**
- 0 ≤ n ≤ 1000 (empty list allowed).
- Values can repeat, so you can't map by value.

## Hints
<details><summary>Hint 1</summary>
Copying `next` alone is easy. What goes wrong when you try to set `random` during the same pass?
</details>
<details><summary>Hint 2</summary>
The random target's copy may not exist yet. What if you create all copies first?
</details>
<details><summary>Hint 3</summary>
Pass 1: map[old] = new Node(old.val). Pass 2: map[old].next = map[old.next], map[old].random = map[old.random] (with null → null).
</details>

## Clarifying Questions
- Can random be null or point to itself? (Yes and yes.)
- Can values repeat? (Yes, so key the map on nodes, not values.)
- Can I modify the original temporarily? (Only the interleave approach does; it must restore it.)

## Example Walkthrough
`[[1,1],[2,1]]`: A(1) → B(2), A.random = B, B.random = B.
- Pass 1: map {A: A', B: B'}.
- Pass 2: A'.next = B', A'.random = map[B] = B'; B'.next = null, B'.random = B'.

## Approaches

### 1. Two-Pass Hashmap ⭐ Go-to: O(n) time, O(n) space
Create copies, then wire pointers through the map.
**Why it's the go-to:** simple to reason about and hard to get wrong; it generalizes to cloning graphs (0133).

### 2. Interleave Copies: O(n) time, O(1) extra space
Insert each copy right after its original (A → A' → B → B' …), so `copy.random = orig.random.next`. Then split the two lists apart, restoring the original. The follow-up answer for O(1) space.

## Dry Run (Approach 1)
`[[7,null],[13,0],[11,4],[10,2],[1,0]]` (nodes n0..n4)

| pass | node | action |
|------|------|--------|
| 1 | n0..n4 | create copies c0..c4, map ni → ci |
| 2 | n0 | c0.next = c1, c0.random = map[null] = null |
| 2 | n1 | c1.next = c2, c1.random = map[n0] = c0 |
| 2 | n2 | c2.next = c3, c2.random = map[n4] = c4 (forward pointer: exists thanks to pass 1) |
| 2 | n3 | c3.next = c4, c3.random = c2 |
| 2 | n4 | c4.next = null, c4.random = c0 |

## Edge Case Check
- Empty list: return null. ✅
- Random to self: map[node] is the copy itself. ✅
- Random to null: map lookup of null must give null (Python dict `{None: None}` seed or a guard). ✅

## ⚠️ Pitfalls
- **Keying by value**: duplicates break it.
- **Null lookups**: C++ `m[nullptr]` default-inserts nullptr (works by accident); Python needs a guard or `{None: None}`; Go map lookup of nil gives nil (zero value).
- **Interleave: not restoring the original list** when splitting.
- **Returning a shallow copy** that points into the original list.

## 🎯 What the Interviewer Wants
- Explain why one pass fails (forward random pointers).
- Map on node identity.
- Mention the O(1)-space interleave trick as the follow-up.

## Follow-ups
- **Clone a general graph:** the same old → new map with BFS/DFS: LC 0133 Clone Graph (not added yet)
- **Tree with random pointers:** LC 1485 Clone Binary Tree With Random Pointer (not added yet)
- **One-pass hashmap:** create copies lazily with a `getClone(node)` helper while walking.
