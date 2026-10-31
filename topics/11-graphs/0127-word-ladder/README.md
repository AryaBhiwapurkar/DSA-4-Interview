---
number: 127
title: Word Ladder
difficulty: Hard
topic: Graphs
pattern: BFS with wildcard buckets
link: https://leetcode.com/problems/word-ladder/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0433 Minimum Genetic Mutation", "0126 Word Ladder II", "0752 Open the Lock"]
---

# 0127. Word Ladder

## ⚡ 30-Second Summary
**Pattern:** BFS on an implicit word graph
**Key insight:** Words are nodes, and two words are adjacent if they differ in one letter. Shortest transformation = BFS. To find neighbours fast, group words by "wildcard patterns" (`h*t`, `*ot`, ...): two words are adjacent iff they share a pattern. Clear each bucket after using it so it's never scanned again.
**Go-to:** BFS with wildcard buckets, O(N · L²) time, O(N · L²) space

## Problem
Given a begin word, an end word and a word list, find the number of words in the shortest sequence from begin to end where each step changes one letter and every word after the first is in the list. Return 0 if there's no such sequence. [LeetCode](https://leetcode.com/problems/word-ladder/)

**Examples:**
```
Input:  beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Why:    hit → hot → dot → dog → cog uses 5 words; nothing shorter exists.

Input:  beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Why:    "cog" isn't in the list, so it can't be reached.
```

**Constraints:**
- 1 ≤ L ≤ 10, up to 5000 words, all the same length, lowercase, distinct; begin ≠ end.
- Comparing all pairs is 2.5·10⁷ · L: too slow-ish; neighbour generation must be smarter.

## Hints
<details><summary>Hint 1</summary>
Shortest number of steps between two nodes in an unweighted graph. Which algorithm?
</details>
<details><summary>Hint 2</summary>
Building all edges by comparing every pair is O(N² · L). Can you find a word's neighbours without looking at every other word?
</details>
<details><summary>Hint 3</summary>
Map each pattern (one letter replaced by '*') to the words that match it. In BFS, for each pattern of the current word, enqueue unseen words in that bucket, then empty the bucket.
</details>

## Clarifying Questions
- Does the count include the begin word? (Yes: number of words, not steps.)
- Is beginWord in the list? (Not necessarily.)
- End word missing from the list? (Return 0.)

## Example Walkthrough
Level 1: hit. Pattern h*t → hot (level 2). hot: *ot → dot, lot (level 3). dot: do* → dog; lot: lo* → log (level 4). dog: *og → cog = end → 5.

## Approaches

### 1. BFS with Letter Substitution: O(N · 26 · L²) time, O(N · L) space
For each popped word, try all L positions × 26 letters and check a hash set of remaining words (delete on visit). Simple; fine for these limits.

### 2. BFS with Wildcard Buckets ⭐ Go-to: O(N · L²) time, O(N · L²) space
Precompute `pattern → words`. Each pattern's bucket is scanned once, then cleared.
**Why it's the go-to:** removes the 26 factor, and the "shared pattern = edge" idea is the insight interviewers look for here.

## Dry Run (Approach 2)
Example 1

| level | word popped | patterns hit (non-empty) | enqueued |
|-------|-------------|--------------------------|----------|
| 1 | hit | h*t → [hot] | hot |
| 2 | hot | *ot → [hot, dot, lot] | dot, lot |
| 3 | dot | do* → [dog] | dog |
| 3 | lot | lo* → [log] | log |
| 4 | dog | *og → [dog, log, cog] | cog = end → **5** |

## Edge Case Check
- End not in the list: 0 before BFS starts. ✅
- Begin and end one letter apart: 2. ✅
- No path (disconnected): BFS empties → 0. ✅

## ⚠️ Pitfalls
- **Off by one**: the answer counts words, so begin is level 1.
- **Not clearing buckets / not marking visited**: common patterns like `*ot` get rescanned for every word, blowing up to O(N²).
- **Mark visited when enqueuing**, not on pop.
- **Python string building** inside the 26 × L loop is the hot spot; buckets avoid most of it.

## 🎯 What the Interviewer Wants
- BFS, with a justification (shortest path, unweighted).
- An efficient neighbour function and its complexity.
- Bonus: bidirectional BFS to shrink the frontier.

## Follow-ups
- **Return all shortest sequences:** LC 0126 Word Ladder II (not added yet), BFS layers + parent map + backtracking.
- **Smaller alphabet, same idea:** [LC 0433 Minimum Genetic Mutation](../0433-minimum-genetic-mutation/)
- **Bidirectional BFS:** expand the smaller frontier each round; meet in the middle.
