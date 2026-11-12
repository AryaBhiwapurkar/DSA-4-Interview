"""
0249. Group Shifted Strings  |  Medium  |  Arrays & Hashing  |  LC Premium
Link: https://leetcode.com/problems/group-shifted-strings/

Problem: Group strings that can be shifted into each other (each letter +k, z wraps to a).

Examples:
  ["abc","bcd","acef","xyz","az","ba","a","z"]  -> [["a","z"],["abc","bcd","xyz"],["acef"],["az","ba"]]
  ["a"]                                         -> [["a"]]
  ["ab","ba","bc"]                              -> [["ab","bc"],["ba"]]

Approaches:
  1. Pairwise compare + grouping     O(n^2 * L) time
  2. Canonical gap key  ⭐           O(N) time, O(N) space   <- go-to (N = total chars)
  (Groups are printed sorted so both approaches compare equal.)
"""

from collections import defaultdict


def same_shift(a: str, b: str) -> bool:
    if len(a) != len(b):
        return False
    d = (ord(b[0]) - ord(a[0])) % 26
    return all((ord(y) - ord(x)) % 26 == d for x, y in zip(a, b))


# ---------- Approach 1: Pairwise Compare ----------
def group_strings_pairwise(strs: list[str]) -> list[list[str]]:
    groups: list[list[str]] = []
    for s in strs:
        for g in groups:
            if same_shift(g[0], s):  # compare to a representative
                g.append(s)
                break
        else:  # no break: start a new group
            groups.append([s])
    return groups


# ---------- Approach 2: Canonical Gap Key ⭐ ----------
def group_strings(strs: list[str]) -> list[list[str]]:
    groups: defaultdict[tuple[int, ...], list[str]] = defaultdict(list)
    for s in strs:
        key = tuple((ord(b) - ord(a)) % 26 for a, b in zip(s, s[1:]))  # gaps survive any shift
        groups[key].append(s)
    return list(groups.values())


# ---------- Driver ----------
def canon(gs: list[list[str]]) -> list[list[str]]:
    return sorted(sorted(g) for g in gs)


if __name__ == "__main__":
    tests = [["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"], ["a"], ["ab", "ba", "bc"]]
    for t in tests:
        print("pairwise:", canon(group_strings_pairwise(t)))
        print("key     :", canon(group_strings(t)))
        print("---")

"""
Syntax notes (Python):
- zip(s, s[1:]) walks consecutive character pairs.
- Tuples are hashable dict keys; tuple[int, ...] annotates a variable-length tuple.
- for ... else: the else runs only when the loop finished without break.
"""
