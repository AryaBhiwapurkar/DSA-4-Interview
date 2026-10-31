---
number: 79
title: Word Search
difficulty: Medium
topic: Backtracking
pattern: Grid DFS backtracking
link: https://leetcode.com/problems/word-search/
lists: [NeetCode 150, LC Top Interview 150]
followup_of: []
related: ["0212 Word Search II", "0200 Number of Islands", "0130 Surrounded Regions"]
---

# 0079. Word Search

## ⚡ 30-Second Summary
**Pattern:** Backtracking DFS on a grid with visited marking
**Key insight:** Try every cell as a start; from a cell matching `word[i]`, mark it used, try the 4 neighbours for `word[i+1]`, then unmark so other paths can use it. Cheap pre-checks (letter counts, start from the rarer end) cut the worst cases.
**Go-to:** DFS with in-place marking + count prune, O(m·n·3^L) time, O(L) space

## Problem
Given an m × n grid of letters and a word, decide whether the word can be traced through horizontally or vertically adjacent cells, using each cell at most once. [LeetCode](https://leetcode.com/problems/word-search/)

**Examples:**
```
Input:  board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Why:    A→B→C across the top, down to the second C, down to E, left to D.

Input:  same board, word = "SEE"
Output: true
Why:    The S on the right edge, then the two E's below it.

Input:  same board, word = "ABCB"
Output: false
Why:    The only B next to that C was already used.
```

**Constraints:**
- 1 ≤ m, n ≤ 6; 1 ≤ L ≤ 15; letters are upper/lowercase English.
- Tiny grid, but 3^15 paths per start is large: pruning matters.

## Hints
<details><summary>Hint 1</summary>
The word can start anywhere. What do you do from each matching cell?
</details>
<details><summary>Hint 2</summary>
A cell can't be reused within the path. How do you mark it, and when must you unmark it?
</details>
<details><summary>Hint 3</summary>
`dfs(r, c, i)`: out of bounds or board[r][c] != word[i] → false; i == L-1 → true. Set board[r][c] = '#', try 4 neighbours with i+1, restore, return.
</details>

## Clarifying Questions
- Diagonal moves? (No.)
- Can I modify the board temporarily? (Usually yes, if restored.)
- Case-sensitive? (Yes.)

## Example Walkthrough
"ABCCED": start at (0,0) 'A'. 'B' is to the right, then 'C'. From (0,2) the next 'C' is below at (1,2), then 'E' at (2,2), then 'D' to its left at (2,1). All 6 letters matched.

## Approaches

### 1. DFS with a Visited Grid: O(m·n·3^L) time, O(m·n + L) space
Separate `visited` matrix, set before exploring and cleared after. Clear, but extra memory and no pruning.

### 2. In-Place Marking + Count Prune ⭐ Go-to: O(m·n·3^L) time, O(L) space
Overwrite the cell with '#' while it's on the path. Before searching, return false if the board lacks enough of some letter, and reverse the word if its last letter is rarer than its first (fewer starting points).
**Why it's the go-to:** same core DFS, no extra grid, and the two prunes are the standard answer to "can you make it faster?".

## Dry Run (Approach 2)
"ABCCED": the board has A ×2 but D ×1, so the go-to searches the reversed word **"DECCBA"**. Neighbour order: down, up, right, left. Every cell before (2,1) fails at once (not 'D').

| step | cell | letter | i | action |
|------|------|--------|---|--------|
| 1 | (2,1) | D | 0 | mark; down out, up (1,1)=F ≠ E, right |
| 2 | (2,2) | E | 1 | mark; down out, up |
| 3 | (1,2) | C | 2 | mark; down is '#', up |
| 4 | (0,2) | C | 3 | mark; down '#', up out, right (0,3)=E ≠ B, left |
| 5 | (0,1) | B | 4 | mark; down F ≠ A, up out, right '#', left |
| 6 | (0,0) | A | 5 | last index → **true**; cells restored while unwinding |

## Edge Case Check
- "ABCB": the board has only one B, so the count prune returns false at once; without the prune, the DFS fails because that B is already on the path. ✅
- 1×1 board, 1-letter word: matches immediately. ✅
- Word longer than m·n: the count prune returns false right away. ✅

## ⚠️ Pitfalls
- **Not restoring the cell** after DFS: later starts see a corrupted board.
- **Check order:** bounds first, then the letter, then `i == L - 1`. Indexing before the bounds check crashes; testing `i == L` before bounds gives false negatives at the grid edge.
- **Python recursion with slicing the word** (`word[1:]`) costs O(L) per call; pass an index.
- **Go:** bytes vs runes; board cells are `byte`, compare with `word[i]` (a byte).

## 🎯 What the Interviewer Wants
- Correct choose / explore / unchoose on a grid.
- Complexity reasoning: 4 choices at the first step, at most 3 after (you can't go back).
- Pruning ideas when asked to speed it up.

## Follow-ups
- **Many words at once:** [LC 0212 Word Search II](../../08-tries/0212-word-search-ii/)
- **Count connected regions instead of one path:** [LC 0200 Number of Islands](../../11-graphs/0200-number-of-islands/)
