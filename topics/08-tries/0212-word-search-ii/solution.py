"""
0212. Word Search II  |  Hard  |  Tries
Link: https://leetcode.com/problems/word-search-ii/

Problem: Return all words that can be traced on the board through
         horizontally/vertically adjacent cells, each cell used once per word.

Examples (printed sorted):
  [[o,a,a,n],[e,t,a,e],[i,h,k,r],[i,f,l,v]], [oath,pea,eat,rain]  -> [eat,oath]
  [[a,b],[c,d]], [abcb]                                          -> []
  [[a]], [a,b]                                                   -> [a]
  [[o,a,b,n],[o,t,a,e],[a,h,k,r],[a,f,l,v]], [oa,oaa]            -> [oa,oaa]

Approaches:
  1. Word search per word        O(W * m*n * 4*3^(L-1))
  2. Trie + backtracking  ⭐      O(m*n * 4*3^(L-1)) worst case   <- go-to
"""

DIRS = ((1, 0), (-1, 0), (0, 1), (0, -1))


# ---------- Approach 1: Word Search Per Word ----------
def find_words_brute(board: list[list[str]], words: list[str]) -> list[str]:
    m, n = len(board), len(board[0])

    def exist(w: str, r: int, c: int, i: int) -> bool:
        if i == len(w):
            return True
        if not (0 <= r < m and 0 <= c < n) or board[r][c] != w[i]:
            return False
        saved, board[r][c] = board[r][c], "#"  # mark visited
        found = any(exist(w, r + dr, c + dc, i + 1) for dr, dc in DIRS)
        board[r][c] = saved  # unmark on backtrack
        return found

    return [w for w in words if any(exist(w, r, c, 0) for r in range(m) for c in range(n))]


# ---------- Approach 2: Trie + Backtracking ⭐ ----------
def find_words(board: list[list[str]], words: list[str]) -> list[str]:
    root: dict = {}
    for w in words:
        node = root
        for ch in w:
            node = node.setdefault(ch, {})
        node["$"] = w  # "$" key holds the finished word
    m, n = len(board), len(board[0])
    res: list[str] = []

    def dfs(r: int, c: int, parent: dict) -> None:
        ch = board[r][c]
        node = parent[ch]
        if "$" in node:
            res.append(node.pop("$"))  # pop: avoid duplicates
        board[r][c] = "#"
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if 0 <= nr < m and 0 <= nc < n and board[nr][nc] in node:  # stay inside the trie
                dfs(nr, nc, node)
        board[r][c] = ch
        if not node:  # prune a fully used branch
            parent.pop(ch)

    for r in range(m):
        for c in range(n):
            if board[r][c] in root:
                dfs(r, c, root)
    return res


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        (["oaan", "etae", "ihkr", "iflv"], ["oath", "pea", "eat", "rain"]),
        (["ab", "cd"], ["abcb"]),
        (["a"], ["a", "b"]),
        (["oabn", "otae", "ahkr", "aflv"], ["oa", "oaa"]),
    ]
    for rows, words in tests:
        print("brute:", sorted(find_words_brute([list(s) for s in rows], words)))  # any order is accepted
        print("trie :", sorted(find_words([list(s) for s in rows], words)))
        print("---")

"""
Syntax notes (Python):
- Nested dicts make a compact trie; a sentinel key ("$") stores the word.
  '#' marks visited cells and is never a trie key, so `in node` rejects it.
- node.pop(key) removes and returns in one step.
- `0 <= r < m` is a chained bounds check.
"""
