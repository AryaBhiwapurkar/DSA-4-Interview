"""
0383. Ransom Note  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/ransom-note/

Problem: Return true if ransomNote can be built from the letters of
         magazine, using each magazine letter at most once.

Examples:
  note="a",  mag="b"    -> False
  note="aa", mag="ab"   -> False
  note="aa", mag="aab"  -> True

Approaches:
  1. Brute force (mark used)   O(m*n) time, O(n) space
  2. Count array  ⭐            O(m+n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Brute Force ----------
def can_construct_brute(note: str, mag: str) -> bool:
    letters = list(mag)  # strings are immutable; use a list we can remove from
    for c in note:
        if c not in letters:
            return False
        letters.remove(c)  # O(n): removes first occurrence
    return True


# ---------- Approach 2: Count Array ⭐ ----------
def can_construct(note: str, mag: str) -> bool:
    cnt = [0] * 26
    for c in mag:
        cnt[ord(c) - ord("a")] += 1
    for c in note:
        i = ord(c) - ord("a")
        cnt[i] -= 1
        if cnt[i] < 0:  # needed more than available
            return False
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    tests = [("a", "b"), ("aa", "ab"), ("aa", "aab")]
    for note, mag in tests:
        print("brute:", can_construct_brute(note, mag))
        print("count:", can_construct(note, mag))
        print("---")

"""
Syntax notes (Python):
- list.remove(x) deletes the first occurrence (ValueError if missing).
- One-liner: not (Counter(note) - Counter(mag)); Counter subtraction
  drops zero and negative counts.
- ord(c) - ord("a") maps 'a'..'z' to 0..25.
"""
