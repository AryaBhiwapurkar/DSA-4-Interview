"""
0433. Minimum Genetic Mutation  |  Medium  |  Graphs
Link: https://leetcode.com/problems/minimum-genetic-mutation/

Problem: 8-letter genes over ACGT. A mutation changes one letter; every
         intermediate must be in the bank. Fewest mutations start -> end, or -1.

Examples:
  AACCGGTT -> AACCGGTA, [AACCGGTA]                      -> 1
  AACCGGTT -> AAACGGTA, [AACCGGTA,AACCGCTA,AAACGGTA]    -> 2
  AAAAACCC -> AACCCCCC, [AAAACCCC,AAACCCCC,AACCCCCC]    -> 3
  AACCGGTT -> AACCGGTA, []                              -> -1
  AACCGGTT -> AACCGGTT, []                              -> 0

Approaches:
  1. BFS scanning the bank             O(B^2 * 8) time, O(B) space
  2. BFS with letter substitution  ⭐   O(B * 8 * 4) time, O(B) space   <- go-to
"""

from collections import deque


# ---------- Approach 1: BFS Scanning the Bank ----------
def min_mutation_scan(start: str, end: str, bank: list[str]) -> int:
    if start == end:
        return 0
    used = [False] * len(bank)
    q = deque([(start, 0)])
    while q:
        g, d = q.popleft()
        for i, b in enumerate(bank):
            if used[i] or sum(x != y for x, y in zip(g, b)) != 1:
                continue
            if b == end:
                return d + 1
            used[i] = True
            q.append((b, d + 1))
    return -1


# ---------- Approach 2: BFS with Letter Substitution ⭐ ----------
def min_mutation(start: str, end: str, bank: list[str]) -> int:
    if start == end:
        return 0
    valid = set(bank)
    if end not in valid:
        return -1
    seen = {start}
    q = deque([(start, 0)])
    while q:
        g, d = q.popleft()
        for i in range(len(g)):
            for ch in "ACGT":
                nxt = g[:i] + ch + g[i + 1 :]
                if nxt in valid and nxt not in seen:
                    if nxt == end:
                        return d + 1
                    seen.add(nxt)  # mark on push
                    q.append((nxt, d + 1))
    return -1


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [
        ("AACCGGTT", "AACCGGTA", ["AACCGGTA"]),
        ("AACCGGTT", "AAACGGTA", ["AACCGGTA", "AACCGCTA", "AAACGGTA"]),
        ("AAAAACCC", "AACCCCCC", ["AAAACCCC", "AAACCCCC", "AACCCCCC"]),
        ("AACCGGTT", "AACCGGTA", []),
        ("AACCGGTT", "AACCGGTT", []),
    ]
    for s, e, bank in tests:
        print("scan :", min_mutation_scan(s, e, bank))
        print("subst:", min_mutation(s, e, bank))
        print("---")

"""
Syntax notes (Python):
- sum(x != y for x, y in zip(a, b)) is the Hamming distance.
- g[:i] + ch + g[i + 1 :] builds a one-letter variant (strings are immutable).
- Trying ch == g[i] is harmless here: g itself is already in seen.
"""
