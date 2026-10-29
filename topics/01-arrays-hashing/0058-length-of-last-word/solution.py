"""
0058. Length of Last Word  |  Easy  |  Arrays & Hashing
Link: https://leetcode.com/problems/length-of-last-word/

Problem: Return the length of the last word in a string of words and
         spaces (a word is a maximal run of non-space characters).

Examples:
  "Hello World"                   -> 5
  "   fly me   to   the moon  "   -> 4
  "luffy is still joyboy"         -> 6
  "a"                             -> 1

Approaches:
  1. Split, take last   O(n) time, O(n) space
  2. Reverse scan  ⭐    O(n) time, O(1) space   <- go-to
"""


# ---------- Approach 1: Split, Take Last ----------
def length_of_last_word_split(s: str) -> int:
    return len(s.split()[-1])


# ---------- Approach 2: Reverse Scan ⭐ ----------
def length_of_last_word(s: str) -> int:
    i = len(s) - 1
    while i >= 0 and s[i] == " ":  # skip trailing spaces
        i -= 1
    length = 0
    while i >= 0 and s[i] != " ":
        length += 1
        i -= 1
    return length


# ---------- Driver ----------
if __name__ == "__main__":
    for s in ["Hello World", "   fly me   to   the moon  ", "luffy is still joyboy", "a"]:
        print("split:", length_of_last_word_split(s))
        print("scan :", length_of_last_word(s))
        print("---")

"""
Syntax notes (Python):
- s.split() (no argument) drops empty strings; s.split(" ") keeps them.
- lst[-1] is the last element.
- Careful: s[-1] is valid Python, so a loop that reaches i = -1 without a
  bound check silently reads the last char instead of stopping.
"""
