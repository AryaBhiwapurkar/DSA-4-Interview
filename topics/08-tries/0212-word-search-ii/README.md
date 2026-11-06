---
number: 212
title: Word Search II
difficulty: Hard
topic: Tries
pattern: Trie + grid backtracking
link: https://leetcode.com/problems/word-search-ii/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: ["0079 Word Search"]
related: ["0079 Word Search", "0208 Implement Trie (Prefix Tree)", "0211 Design Add and Search Words Data Structure"]
---

# 0212. Word Search II

## ⚡ 30-Second Summary
**Pattern:** Trie of all words + one backtracking DFS from every cell
**Key insight:** Running 0079 once per word repeats the same grid walks for every shared prefix. Put all words in a trie and walk the grid and the trie together: a path stops as soon as it leaves the trie, and a node holding a word means "found". Remove found words (and prune empty trie branches) to avoid duplicates and dead walks.
**Go-to:** Trie + DFS with pruning, O(m·n·4·3^(L-1)) worst case, O(total word chars) space

## Problem
Given an m × n board of letters and a list of words, return every word that can be traced on the board by moving horizontally or vertically between adjacent cells, using each cell at most once per word. Any order. [LeetCode](https://leetcode.com/problems/word-search-ii/)

**Examples:**
```
Input:  board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
        words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
Why:    "oath" and "eat" can be traced through adjacent cells; "pea" and "rain" can't.

Input:  board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
Why:    "abcb" would need to reuse the cell "b".
```

**Constraints:**
- 1 ≤ m, n ≤ 12; up to 3·10⁴ words of length ≤ 10; words are unique.

## Hints
<details><summary>Hint 1</summary>
Solving 0079 for each word separately is too slow with 3·10⁴ words. What work is shared between words?
</details>
<details><summary>Hint 2</summary>
Common prefixes. Which structure lets you test "is this path a prefix of any word?" one letter at a time?
</details>
<details><summary>Hint 3</summary>
Build a trie storing the full word at its end node. DFS from each cell carrying the current trie node; mark visited cells; when a node has a word, record it and clear it. Prune children that become empty.
</details>

## Clarifying Questions
- Can a cell be reused within one word? (No.)
- Diagonal moves? (No.)
- Output order? (Any.)

## Example Walkthrough
Example 1: from (0,0) 'o' the trie has "o" → walk to 'a' (0,1), 't' (1,1), 'h' (2,1): "oath" found. From (1,3) 'e' → 'a' (1,2) → 't' (1,1): "eat" found. No path starts "pe" or "rai" usefully.

## Approaches

### 1. Word Search Per Word: O(W · m·n·4·3^(L-1))
Run the 0079 backtracking for each word. Correct but repeats work across shared prefixes.

### 2. Trie + Backtracking ⭐ Go-to: O(m·n·4·3^(L-1)) worst case
One DFS per starting cell explores all words at once; trie pruning kills paths that match no word.
**Why it's the go-to:** the standard optimal approach, and pruning makes it fast in practice.

## Dry Run (Approach 2)
`[["a","b"],["c","d"]]`, words ["abcb"]

| path | trie node | next | result |
|------|-----------|------|--------|
| a (0,0) | a | b (0,1) | continue |
| ab | ab | unvisited neighbour of (0,1) is d (1,1) | trie expects 'c' after "ab" → stop |
| others | | | no other start matches 'a' |
| result | | | **[]** |

## Edge Case Check
- Same word reachable twice: clearing the word at its node prevents duplicates. ✅
- Word that's a prefix of another ("oa", "oath"): both recorded on the same walk. ✅
- 1×1 board: single-letter words only. ✅

## ⚠️ Pitfalls
- **Not marking cells as visited** (or not unmarking on backtrack).
- **Duplicates in the output** when a word can be found from several paths: clear it after recording.
- **No pruning**: TLE on large inputs; remove trie leaves whose words were all found.
- **Python recursion + string building per step** is slow; store the word in the trie node instead.

## 🎯 What the Interviewer Wants
- Recognise the shared-prefix waste in the per-word approach and bring in a trie.
- Correct backtracking with visited marking.
- Mention pruning found branches.

## Follow-ups
- **Single word:** [LC 0079 Word Search](../../10-backtracking/0079-word-search/)
- **Trie basics:** [LC 0208 Implement Trie (Prefix Tree)](../0208-implement-trie-prefix-tree/)
- **Wildcards in the words:** combine with [LC 0211](../0211-design-add-and-search-words-data-structure/)
