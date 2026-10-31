---
number: 433
title: Minimum Genetic Mutation
difficulty: Medium
topic: Graphs
pattern: BFS over strings
link: https://leetcode.com/problems/minimum-genetic-mutation/
lists: [LC Top Interview 150]
followup_of: []
related: ["0127 Word Ladder", "0752 Open the Lock"]
---

# 0433. Minimum Genetic Mutation

## ⚡ 30-Second Summary
**Pattern:** BFS on an implicit graph of strings
**Key insight:** Each valid gene is a node; two genes are connected if they differ in exactly one position. "Fewest mutations" is a shortest path in an unweighted graph, so BFS. Generate neighbours by trying all 8 × 3 single-letter changes and keeping those in the bank.
**Go-to:** BFS with letter substitution, O(B · 8 · 4) time, O(B) space

## Problem
Genes are 8-letter strings over A, C, G, T. One mutation changes one letter, and every intermediate (and the target) must be in a given bank. Return the minimum number of mutations from start to end, or -1. [LeetCode](https://leetcode.com/problems/minimum-genetic-mutation/)

**Examples:**
```
Input:  startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1
Why:    Change the last T to A; the result is in the bank.

Input:  startGene = "AACCGGTT", endGene = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2
Why:    AACCGGTT → AACCGGTA → AAACGGTA, each step in the bank.

Input:  startGene = "AAAAACCC", endGene = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
Output: 3
Why:    One A becomes C per step, through each bank entry in turn.
```

**Constraints:**
- Genes have length 8; bank size 0..10. Start need not be in the bank.

## Hints
<details><summary>Hint 1</summary>
What are the nodes and edges? What does "minimum number of steps" suggest?
</details>
<details><summary>Hint 2</summary>
From one gene, how many one-letter changes are possible? Which ones are allowed?
</details>
<details><summary>Hint 3</summary>
BFS from start with a visited set; for each popped gene try every position × every other letter, enqueue bank members not yet seen, return depth + 1 when you produce the end gene.
</details>

## Clarifying Questions
- Does start need to be in the bank? (No.)
- End not in the bank? (Then -1.)
- start == end? (0 mutations.)

## Example Walkthrough
Example 2: level 0 = {AACCGGTT}. Its only bank neighbour is AACCGGTA (level 1). From there, changing position 2 C → A gives AAACGGTA = end → 2.

## Approaches

### 1. BFS Scanning the Bank: O(B² · 8) time, O(B) space
For each popped gene, compare against every bank string and enqueue those differing in exactly one position. Fine for B ≤ 10, worse for big banks.

### 2. BFS with Letter Substitution ⭐ Go-to: O(B · 8 · 4) time, O(B) space
Generate the 24 one-letter variants and look each up in a hash set of the bank.
**Why it's the go-to:** independent of bank size per step, and it's the same template as 0127 Word Ladder.

## Dry Run (Approach 2)
Example 2

| pop | depth | variants in bank, not seen | action |
|-----|-------|----------------------------|--------|
| AACCGGTT | 0 | AACCGGTA | push (1) |
| AACCGGTA | 1 | AAACGGTA (pos 2 C→A) | it's the end → **2** |

## Edge Case Check
- End not in bank: -1 immediately. ✅
- start == end: 0. ✅
- Empty bank: -1 (unless start == end). ✅

## ⚠️ Pitfalls
- **DFS** finds *a* path, not the shortest, unless you explore everything.
- **No visited set**: genes bounce back and forth forever.
- **Mark visited when pushing**, not when popping, to avoid duplicates in the queue.
- **C++ string mutation**: change `s[i]`, test, then restore it before the next letter.

## 🎯 What the Interviewer Wants
- Model as an unweighted graph → BFS.
- Neighbour generation by substitution and a hash-set lookup.

## Follow-ups
- **Bigger alphabet and longer words, count path length:** [LC 0127 Word Ladder](../0127-word-ladder/)
- **Wheel lock with dead ends:** LC 0752 Open the Lock (not added yet), same BFS.
- **Bidirectional BFS** to cut the frontier size on large inputs.
