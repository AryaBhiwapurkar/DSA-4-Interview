"""
0205. Isomorphic Strings  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/isomorphic-strings/

Problem: Return true if each char of s can be replaced consistently to
         get t, with no two different chars of s mapping to the same
         char of t (one-to-one mapping).

Examples:
  s="egg",   t="add"    -> True
  s="foo",   t="bar"    -> False
  s="paper", t="title"  -> True
  s="badc",  t="baba"   -> False

Approaches:
  1. First-occurrence signature   O(n) time, O(n) space
  2. Two maps  ⭐                  O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: First-Occurrence Signature ----------
def signature(s: str) -> list[int]:
    first: dict[str, int] = {}
    return [first.setdefault(c, i) for i, c in enumerate(s)]


def is_isomorphic_signature(s: str, t: str) -> bool:
    return len(s) == len(t) and signature(s) == signature(t)


# ---------- Approach 2: Two Maps ⭐ ----------
def is_isomorphic(s: str, t: str) -> bool:
    if len(s) != len(t):
        return False
    st: dict[str, str] = {}
    ts: dict[str, str] = {}
    for a, b in zip(s, t):
        if a not in st and b not in ts:
            st[a] = b
            ts[b] = a
        elif st.get(a) != b or ts.get(b) != a:
            return False  # breaks one direction of the bijection
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("egg", "add"), ("foo", "bar"), ("paper", "title"), ("badc", "baba")]
    for s, t in tests:
        print("signature:", is_isomorphic_signature(s, t))
        print("two maps :", is_isomorphic(s, t))
        print("---")

"""
Syntax notes (Python):
- dict.setdefault(k, v) inserts v if k is missing and returns the stored value.
- dict.get(k) returns None for a missing key (no KeyError).
- One-liner: len(set(s)) == len(set(t)) == len(set(zip(s, t))).
"""
