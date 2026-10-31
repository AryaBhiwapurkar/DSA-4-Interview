"""
0127. Word Ladder  |  Hard  |  Graphs
Link: https://leetcode.com/problems/word-ladder/

Problem: Number of words in the shortest begin -> end chain where each step
         changes one letter and every later word is in the list; 0 if none.

Examples:
  hit -> cog, [hot,dot,dog,lot,log,cog]  -> 5
  hit -> cog, [hot,dot,dog,lot,log]      -> 0
  a -> c, [a,b,c]                        -> 2
  hot -> dog, [hot,dog]                  -> 0 (two letters differ)

Approaches:
  1. BFS with letter substitution    O(N * 26 * L^2) time, O(N * L) space
  2. BFS with wildcard buckets  ⭐    O(N * L^2) time, O(N * L^2) space   <- go-to
"""

from collections import defaultdict, deque
from string import ascii_lowercase


# ---------- Approach 1: BFS with Letter Substitution ----------
def ladder_length_subst(begin: str, end: str, words: list[str]) -> int:
    left = set(words)  # unvisited dictionary words
    if end not in left:
        return 0
    left.discard(begin)
    q = deque([(begin, 1)])
    while q:
        w, d = q.popleft()
        for i in range(len(w)):
            for ch in ascii_lowercase:
                nxt = w[:i] + ch + w[i + 1 :]
                if nxt in left:
                    if nxt == end:
                        return d + 1
                    left.remove(nxt)  # remove = mark visited
                    q.append((nxt, d + 1))
    return 0


# ---------- Approach 2: BFS with Wildcard Buckets ⭐ ----------
def ladder_length(begin: str, end: str, words: list[str]) -> int:
    if end not in words:
        return 0
    buckets: defaultdict[str, list[str]] = defaultdict(list)  # "h*t" -> words matching it
    for w in words:
        for i in range(len(w)):
            buckets[w[:i] + "*" + w[i + 1 :]].append(w)
    seen = {begin}
    q = deque([(begin, 1)])
    while q:
        w, d = q.popleft()
        for i in range(len(w)):
            p = w[:i] + "*" + w[i + 1 :]
            for nb in buckets.get(p, []):
                if nb in seen:
                    continue
                if nb == end:
                    return d + 1
                seen.add(nb)
                q.append((nb, d + 1))
            buckets[p] = []  # never scan this pattern again
    return 0


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ("hit", "cog", ["hot", "dot", "dog", "lot", "log", "cog"]),
        ("hit", "cog", ["hot", "dot", "dog", "lot", "log"]),
        ("a", "c", ["a", "b", "c"]),
        ("hot", "dog", ["hot", "dog"]),
    ]
    for b, e, words in tests:
        print("subst  :", ladder_length_subst(b, e, words))
        print("buckets:", ladder_length(b, e, words))
        print("---")

"""
Syntax notes (Python):
- buckets.get(p, []) reads without inserting; buckets[p] on a defaultdict would insert.
- string.ascii_lowercase is "abcdefghijklmnopqrstuvwxyz".
- set.discard ignores missing keys; set.remove raises KeyError.
"""
