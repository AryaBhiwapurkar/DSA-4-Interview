"""
0269. Alien Dictionary  |  Hard  |  Advanced Graphs
Link: https://leetcode.com/problems/alien-dictionary/

Problem: Words are sorted by an unknown alphabet. Return a letter order
         consistent with them, or "" if none exists.

Examples:
  ["wrt","wrf","er","ett","rftt"]  -> "wertf"
  ["z","x"]                        -> "zx"
  ["z","x","z"]                    -> "" (z<x and x<z: cycle)
  ["abc","ab"]                     -> "" (longer word before its prefix)
  ["z","z"]                        -> "z"

Approaches:
  1. DFS post-order (three colors)  O(C) time, O(1) space (26 letters)
  2. Kahn's BFS  ⭐                  O(C) time, O(1) space   <- go-to
  C = total characters in all words.
"""

from collections import deque


def build_graph(words: list[str]) -> dict[str, set[str]] | None:
    """Letter -> letters that come after it; None if a word precedes its own prefix."""
    adj: dict[str, set[str]] = {c: set() for w in words for c in w}  # every letter is a node
    for a, b in zip(words, words[1:]):
        for x, y in zip(a, b):
            if x != y:
                adj[x].add(y)  # first difference only
                break
        else:
            if len(a) > len(b):  # "abc" before "ab"
                return None
    return adj


# ---------- Approach 1: DFS post-order ----------
def alien_order_dfs(words: list[str]) -> str:
    adj = build_graph(words)
    if adj is None:
        return ""
    color: dict[str, int] = {}  # missing = unvisited, 1 = on path, 2 = done
    out: list[str] = []

    def dfs(u: str) -> bool:
        color[u] = 1
        for v in sorted(adj[u]):
            if color.get(v) == 1:  # back edge: cycle
                return False
            if v not in color and not dfs(v):
                return False
        color[u] = 2
        out.append(u)
        return True

    for c in sorted(adj):
        if c not in color and not dfs(c):
            return ""
    return "".join(reversed(out))  # post-order reversed = topological order


# ---------- Approach 2: Kahn's BFS ⭐ ----------
def alien_order(words: list[str]) -> str:
    adj = build_graph(words)
    if adj is None:
        return ""
    indeg = {c: 0 for c in adj}
    for nbrs in adj.values():
        for v in nbrs:
            indeg[v] += 1
    q = deque(sorted(c for c in adj if indeg[c] == 0))
    out: list[str] = []
    while q:
        u = q.popleft()
        out.append(u)
        for v in sorted(adj[u]):
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)
    return "".join(out) if len(out) == len(adj) else ""  # leftovers mean a cycle


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [["wrt", "wrf", "er", "ett", "rftt"], ["z", "x"], ["z", "x", "z"], ["abc", "ab"], ["z", "z"]]
    for w in tests:
        print(f'dfs : "{alien_order_dfs(w)}"')
        print(f'kahn: "{alien_order(w)}"')
        print("---")

"""
Syntax notes (Python):
- for/else: the else runs only if the loop didn't `break` (no differing letter found).
- zip(words, words[1:]) walks consecutive pairs; zip(a, b) stops at the shorter word.
- `X | None` return type (3.10+) marks an invalid input without exceptions.
- sorted() over sets keeps the output deterministic.
"""
