---
number: 269
title: Alien Dictionary
difficulty: Hard
topic: Advanced Graphs
pattern: Topological sort on chars
link: https://leetcode.com/problems/alien-dictionary/
lists: [NeetCode 150]
followup_of: ["0210 Course Schedule II"]
related: ["0207 Course Schedule", "0953 Verifying an Alien Dictionary"]
---

# 0269. Alien Dictionary

## ⚡ 30-Second Summary
**Pattern:** Build a graph from adjacent pairs, then topological sort
**Key insight:** Only **adjacent** words carry information, and only their **first differing letter**: `a[j] < b[j]`. That's a directed edge. A topological order of the letters is the alphabet; a cycle or "longer word before its own prefix" means invalid.
**Go-to:** Kahn's BFS over letters, O(C) time (C = total characters), O(1) extra space (≤ 26 letters)

## Problem
You get a list of words that is sorted in an alien language's alphabet (which uses lowercase English letters in an unknown order). Return any ordering of the letters that is consistent with the list, or `""` if the list is impossible. (LeetCode Premium.) [LeetCode](https://leetcode.com/problems/alien-dictionary/)

**Examples:**
```
Input:  words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Why:    Pairs give t<f, w<e, r<t, e<r. Chained: w<e<r<t<f.

Input:  words = ["z","x"]
Output: "zx"
Why:    One pair, one rule: z before x.

Input:  words = ["z","x","z"]
Output: ""
Why:    z<x from the first pair and x<z from the second: a cycle, so no alphabet works.
```

**Constraints:**
- Up to 100 words of length ≤ 100, so C ≤ 10⁴.
- Only lowercase letters: at most 26 nodes.
- Any valid order is accepted when several exist.

## Hints
<details><summary>Hint 1</summary>
Compare two adjacent words. What is the one thing their ordering tells you about the alphabet?
</details>
<details><summary>Hint 2</summary>
Each such fact is "letter x comes before letter y". You now have a dependency graph. What problem is this, from the Graphs topic?
</details>
<details><summary>Hint 3</summary>
For each adjacent pair, find the first differing index j and add edge a[j]→b[j]; if there's no difference and a is longer than b, return "". Register every letter as a node. Kahn's: start from indegree-0 letters; if the output is shorter than the number of letters, there's a cycle.
</details>

## Clarifying Questions
- Must every letter that appears be in the output, even without constraints? (Yes.)
- Which order if several are valid? (Any.)
- What if a word is followed by its own prefix, like "abc", "ab"? (Invalid, return "".)
- Only adjacent pairs, or all pairs? (Adjacent pairs are enough: the order is transitive.)

## Example Walkthrough
Example 1, pair by pair:
- "wrt" vs "wrf": first difference at index 2 → t < f.
- "wrf" vs "er": index 0 → w < e.
- "er" vs "ett": index 1 → r < t.
- "ett" vs "rftt": index 0 → e < r.
Edges w→e→r→t→f. One chain, so the answer is unique: "wertf".

## Approaches

### 1. DFS Post-Order (Three Colors): O(C) time, O(1) space
DFS from each unvisited letter; append a letter after all its successors finish; reverse at the end. Seeing a "gray" (on-path) letter means a cycle.

### 2. Kahn's BFS ⭐ Go-to: O(C) time, O(1) space
Compute indegrees, queue all indegree-0 letters, pop and decrement successors. If fewer than all letters come out, there's a cycle.
**Why it's the go-to:** iterative, and cycle detection is a single length check at the end, which is easy to explain.

## Dry Run (Approach 2)
Example 1. Edges: w→e, e→r, r→t, t→f.

| step | queue | pop | output | indegree changes |
|------|-------|-----|--------|------------------|
| init | [w] | | "" | e1 r1 t1 f1 |
| 1 | [] | w | "w" | e → 0, push e |
| 2 | [] | e | "we" | r → 0, push r |
| 3 | [] | r | "wer" | t → 0, push t |
| 4 | [] | t | "wert" | f → 0, push f |
| 5 | [] | f | "wertf" | |

5 letters out of 5 → **"wertf"**.

## Edge Case Check
- Cycle (example 3): z and x both keep indegree 1, nothing starts → "" ✅
- Prefix violation `["abc","ab"]` → "" before building anything. ✅
- `["z","z"]`: no edges, one letter → "z". ✅
- Letters with no constraints still appear (they start with indegree 0). ✅

## ⚠️ Pitfalls
- **Comparing past the first difference**: only the first differing letter is a rule; the rest says nothing.
- **Missing the prefix case**: `"abc"` before `"ab"` is invalid and must return "".
- **Duplicate edges inflate indegree** (and then a letter never reaches 0): use a set of successors.
- **Forgetting letters that never appear in an edge**: register every character as a node first.
- **Python:** for/else is handy here, but the else belongs to the inner `for`; indent carefully.

## 🎯 What the Interviewer Wants
- Turn word order into edges correctly (first difference, adjacent pairs only).
- Handle the prefix case unprompted.
- Reuse the topological sort template, with cycle detection.

## Follow-ups
- **Plain topo sort over a given edge list:** [LC 0210 Course Schedule II](../../11-graphs/0210-course-schedule-ii/)
- **Just detect whether an order exists:** [LC 0207 Course Schedule](../../11-graphs/0207-course-schedule/)
- **Order given; check whether words are sorted:** LC 0953 Verifying an Alien Dictionary (not added yet)
- **Return the lexicographically smallest valid order?** Swap the queue for a min-heap.
