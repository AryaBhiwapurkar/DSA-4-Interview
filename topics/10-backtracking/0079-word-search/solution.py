"""
0079. Word Search  |  Medium  |  Backtracking
Link: https://leetcode.com/problems/word-search/

Problem: Can `word` be traced on a letter grid through 4-adjacent
         cells, each cell used at most once?

Examples (board B = ABCE / SFCS / ADEE):
  B, "ABCCED"  -> true
  B, "SEE"     -> true
  B, "ABCB"    -> false
  ["a"], "a"   -> true
  ["ab"], "ba" -> true
  ["aa"], "aaa" -> false (too long)

Approaches:
  1. DFS + visited grid               O(m*n*3^L) time, O(m*n + L) space
  2. In-place mark + count prune  ⭐   O(m*n*3^L) time, O(L) space   <- go-to
"""

from collections import Counter

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: DFS + Visited Grid ----------
def exist_visited(board: list[list[str]], word: str) -> bool:
    m, n = len(board), len(board[0])
    vis = [[False] * n for _ in range(m)]

    def dfs(r: int, c: int, i: int) -> bool:
        if not (0 <= r < m and 0 <= c < n) or vis[r][c] or board[r][c] != word[i]:
            return False
        if i == len(word) - 1:
            return True
        vis[r][c] = True
        found = any(dfs(r + dr, c + dc, i + 1) for dr, dc in DIRS)
        vis[r][c] = False
        return found

    return any(dfs(r, c, 0) for r in range(m) for c in range(n))


# ---------- Approach 2: In-Place Mark + Count Prune ⭐ ----------
def exist(board: list[list[str]], word: str) -> bool:
    m, n = len(board), len(board[0])
    if len(word) > m * n:
        return False
    have = Counter(ch for row in board for ch in row)
    if any(have[ch] < k for ch, k in Counter(word).items()):
        return False
    if have[word[-1]] < have[word[0]]:
        word = word[::-1]  # start from the rarer end

    def dfs(r: int, c: int, i: int) -> bool:
        if not (0 <= r < m and 0 <= c < n) or board[r][c] != word[i]:
            return False
        if i == len(word) - 1:
            return True
        board[r][c] = "#"  # on the path: can't be reused
        found = any(dfs(r + dr, c + dc, i + 1) for dr, dc in DIRS)
        board[r][c] = word[i]  # unchoose
        return found

    return any(dfs(r, c, 0) for r in range(m) for c in range(n))


# ---------- Driver ----------
if __name__ == "__main__":
    B = ["ABCE", "SFCS", "ADEE"]
    tests = [(B, "ABCCED"), (B, "SEE"), (B, "ABCB"), (["a"], "a"), (["ab"], "ba"), (["aa"], "aaa")]
    for rows, word in tests:
        print("visited:", exist_visited([list(s) for s in rows], word))
        print("inplace:", exist([list(s) for s in rows], word))
        print("---")

"""
Syntax notes (Python):
- any(generator) short-circuits: later directions aren't tried once one is True.
- Counter(word).items() gives (letter, count); missing keys in a Counter read as 0.
- word[::-1] reverses a string.
"""
