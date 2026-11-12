"""
0890. Find and Replace Pattern  |  Medium  |  Arrays & Hashing
Link: https://leetcode.com/problems/find-and-replace-pattern/

Problem: Return the words that match the pattern under a one-to-one letter mapping.

Examples:
  ["abc","deq","mee","aqq","dkd","ccc"], "abb"  -> ["mee","aqq"]
  ["a","b","c"], "a"                            -> ["a","b","c"]
  ["xyz","xxy","yyx"], "abc"                    -> ["xyz"]

Approaches:
  1. Two-map bijection check  ⭐       O(N) time, O(1) space per word   <- go-to
  2. First-occurrence signature        O(N) time, O(L) space
"""


def matches(w: str, p: str) -> bool:
    p2w: dict[str, str] = {}
    w2p: dict[str, str] = {}
    for a, b in zip(p, w):
        if p2w.get(a, b) != b or w2p.get(b, a) != a:  # either direction already mapped elsewhere
            return False
        p2w[a], w2p[b] = b, a
    return True


# ---------- Approach 1: Two-map Bijection ⭐ ----------
def find_and_replace_pattern(words: list[str], pattern: str) -> list[str]:
    return [w for w in words if matches(w, pattern)]


# ---------- Approach 2: First-occurrence Signature ----------
def signature(s: str) -> list[int]:
    first: dict[str, int] = {}
    return [first.setdefault(c, i) for i, c in enumerate(s)]  # "abb" -> [0,1,1]


def find_and_replace_pattern_sig(words: list[str], pattern: str) -> list[str]:
    target = signature(pattern)
    return [w for w in words if signature(w) == target]


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [(["abc", "deq", "mee", "aqq", "dkd", "ccc"], "abb"), (["a", "b", "c"], "a"),
             (["xyz", "xxy", "yyx"], "abc")]
    for words, p in tests:
        print("two maps :", find_and_replace_pattern(words, p))
        print("signature:", find_and_replace_pattern_sig(words, p))
        print("---")

"""
Syntax notes (Python):
- d.get(k, default) != v is a compact "mapped to something else?" test.
- d.setdefault(c, i) inserts i only the first time and returns the stored value.
- zip(p, w) pairs letters position by position.
"""
