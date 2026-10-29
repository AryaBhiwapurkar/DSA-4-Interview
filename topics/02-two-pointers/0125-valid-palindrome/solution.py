"""
0125. Valid Palindrome  |  Easy  |  Two Pointers
Link: https://leetcode.com/problems/valid-palindrome/

Problem: After lowercasing and removing non-alphanumeric characters,
         does the string read the same forwards and backwards?

Examples:
  "A man, a plan, a canal: Panama"  -> True
  "race a car"                      -> False
  " "                               -> True
  "0P"                              -> False

Approaches:
  1. Clean + reverse      O(n) time, O(n) space
  2. Two pointers  ⭐      O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Clean + Reverse ----------
def is_palindrome_clean(s: str) -> bool:
    t = [c.lower() for c in s if c.isalnum()]
    return t == t[::-1]


# ---------- Approach 2: Two Pointers ⭐ ----------
def is_palindrome(s: str) -> bool:
    l, r = 0, len(s) - 1
    while l < r:
        while l < r and not s[l].isalnum():  # skip junk on the left
            l += 1
        while l < r and not s[r].isalnum():  # skip junk on the right
            r -= 1
        if s[l].lower() != s[r].lower():
            return False
        l, r = l + 1, r - 1
    return True


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["A man, a plan, a canal: Panama", "race a car", " ", "0P"]:
        print("clean   :", is_palindrome_clean(s))
        print("pointers:", is_palindrome(s))
        print("---")

"""
Syntax notes (Python):
- str.isalnum() is True for letters and digits.
- seq[::-1] is a reversed copy (works on lists and strings).
- Note: Python's isalnum accepts Unicode letters too; fine for ASCII input.
"""
