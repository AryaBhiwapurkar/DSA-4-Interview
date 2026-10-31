---
number: 133
title: Clone Graph
difficulty: Medium
topic: Graphs
pattern: DFS + hashmap old→new
link: https://leetcode.com/problems/clone-graph/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0138 Copy List with Random Pointer", "1490 Clone N-ary Tree"]
---

# 0133. Clone Graph

## ⚡ 30-Second Summary
**Pattern:** Graph traversal + hashmap from original node to its copy
**Key insight:** The map does two jobs: it is the visited set, and it gives the already-made copy when a cycle leads back to a node. Create the copy *before* recursing into neighbours, or a cycle recurses forever.
**Go-to:** DFS with an old → new map, O(V + E) time, O(V) space

## Problem
Given a reference to one node of a connected undirected graph (each node has a value and a list of neighbours), return a deep copy of the whole graph. Values are 1..n and unique; the test input is an adjacency list where entry i lists the neighbours of node i+1. [LeetCode](https://leetcode.com/problems/clone-graph/)

**Examples:**
```
Input:  adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Why:    A 4-cycle 1-2-3-4-1; the copy has the same shape but brand-new nodes.

Input:  adjList = [[]]
Output: [[]]
Why:    A single node with no neighbours.

Input:  adjList = []
Output: []
Why:    No graph: the input node is null, return null.
```

**Constraints:**
- 0 ≤ n ≤ 100, values unique 1..n, no self-loops or repeated edges, graph connected.

## Hints
<details><summary>Hint 1</summary>
Copying node by node, what goes wrong when the graph has a cycle?
</details>
<details><summary>Hint 2</summary>
You need to know "have I already copied this node, and where is the copy?". Which structure answers both?
</details>
<details><summary>Hint 3</summary>
`clone(node)`: if node in map, return map[node]. Else create copy, store it in the map, then for each neighbour append `clone(neighbour)` to the copy's list.
</details>

## Clarifying Questions
- Directed or undirected? (Undirected: each edge appears in both lists.)
- Can the input be null? (Yes, return null.)
- Is the graph connected? (Yes, so one traversal reaches every node.)

## Example Walkthrough
`[[2,4],[1,3],[2,4],[1,3]]`: clone 1 (map {1}), go to 2 → clone 2, its neighbour 1 is already in the map so link to copy 1; go to 3 → clone 3, links to copy 2 and recurses to 4 → clone 4, links to copy 1 and copy 3. Back up, 1's second neighbour 4 is already copied.

## Approaches

### 1. DFS + Map ⭐ Go-to: O(V + E) time, O(V) space
Recursive clone that memoizes copies.
**Why it's the go-to:** about eight lines, and the "insert before recursing" detail is easy to explain.

### 2. BFS + Map: O(V + E) time, O(V) space
Copy the start node, queue it. For each popped node, for each neighbour: if not in the map, copy it and queue it; then append the neighbour's copy to the popped node's copy. Same idea, no recursion depth.

## Dry Run (Approach 1)
`[[2,4],[1,3],[2,4],[1,3]]`

| call | node | in map? | action | map after |
|------|------|---------|--------|-----------|
| 1 | 1 | no | create 1', recurse on 2 | {1} |
| 2 | 2 | no | create 2', neighbour 1 → found, recurse on 3 | {1,2} |
| 3 | 3 | no | create 3', neighbour 2 → found, recurse on 4 | {1,2,3} |
| 4 | 4 | no | create 4', neighbours 1, 3 → both found | {1,2,3,4} |
| back in 1 | 4 | yes | link 1' → 4' | |

Result: 1'[2',4'], 2'[1',3'], 3'[2',4'], 4'[1',3'].

## Edge Case Check
- Null input: return null. ✅
- Single node, no neighbours: one new node, empty list. ✅
- Cycle: the map stops infinite recursion. ✅

## ⚠️ Pitfalls
- **Adding to the map after the recursive calls** → infinite recursion on any cycle.
- **Returning the original neighbour** instead of its copy (a shallow copy that looks right when printed).
- **Keying the map by value** is fine here (values unique), but keying by node identity is the general solution.
- **C++ `map[node]` lookups** insert nulls; use `find`/`count`.

## 🎯 What the Interviewer Wants
- The map as visited + copy lookup.
- Correct handling of cycles and null.
- DFS or BFS with the same complexity, and when you'd prefer BFS (deep graphs).

## Follow-ups
- **Same idea on a list with random pointers:** [LC 0138 Copy List with Random Pointer](../../06-linked-list/0138-copy-list-with-random-pointer/)
- **Directed graph or disconnected input:** loop over all nodes as starts with the same map.
